#include "threepp/threepp.hpp"
using namespace threepp;
#include <cmath>
float sinus_bølge(float x,float A=1,float f=1,float b=0) {
    return sin(x)*2;
}
int main() {
    Canvas canvas("threepp");
    GLRenderer renderer(canvas);
    auto scene = Scene::create();
    scene->background = Color::white;
    auto camera = PerspectiveCamera::create(60, canvas.aspect(), 0.1f, 1000);
    camera->position.z = 5;

    // håndterer vindusstørrelseendringer
    canvas.onWindowResize([&](WindowSize size) {
    camera->aspect = size.aspect();
    camera->updateProjectionMatrix();
    renderer.setSize(size);
    });

    // lagger alt som skal i scenen
    auto light = DirectionalLight::create();
    light->position.set(1, 2, 3);
    scene->add(light);
    scene->add(AmbientLight::create(0xffffff, 0.4f)); // hvitt lys med 40 % styrke

    // lager geomtri i scenen
    auto geometry = BoxGeometry::create(0.5, 0.5, 0.5);


    std::vector<Color> colors{Color::red, Color::blue};
    std::vector<std::shared_ptr<MeshStandardMaterial>> material;
    std::vector<std::shared_ptr<Mesh>> box;
    for (int i = 0; i < 8; i++) {
        //auto box = Mesh::create(geometry, material);
        material.push_back(MeshStandardMaterial::create());
        material[i]->color = Color::blue;
        box.push_back(Mesh::create(geometry, material[i]));
        box[i]->position.set(-3.5+i, 0, 0);
        scene->add(box[i]);
    }

    // Space knapp bytter farge på annenhver
    int Space_click = 0;
    canvas.onKeyPressed([&](KeyEvent event) {

        if (event.key == Key::SPACE) {
            Space_click++;
            for (int i = 0; i < 8; i++) {
                if(i%2==0){
                    material[i]->color = colors[Space_click%2];
                }else {
                    material[i]->color = colors[(Space_click+1)%2];

                }
            }

        }
    });

    // animasjons loop
    Clock clock;
    canvas.animate([&] {
    const float dt = clock.getDelta();
        for (int i = 0; i < 8; i++) {
            box[i]->rotation.y -= 1.0f * dt;
            if(i%2==0){
                box[i]->position.y = sinus_bølge(clock.getElapsedTime(),2,1,0);
            }else {
                box[i]->position.y = sinus_bølge(clock.getElapsedTime()+3.14f,2,1,0);
            }
        }

    renderer.render(*scene, *camera);
    });
}