#include "threepp/threepp.hpp"
using namespace threepp;
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
    auto material = MeshStandardMaterial::create();
    material->color = Color::orange;

    std::vector<std::shared_ptr<Mesh>> box;
    for (int i = 0; i < 8; i++) {
        //auto box = Mesh::create(geometry, material);
        box.push_back(Mesh::create(geometry, material));
        box[i]->position.set(-3.5+i, 0, 0);
        scene->add(box[i]);
    }

    // animasjons loop
    Clock clock;
    canvas.animate([&] {
    const float dt = clock.getDelta();
        for (int i = 0; i < 8; i++) {
            box[i]->rotation.y -= 1.0f * dt;
        }

    renderer.render(*scene, *camera);
    });
}