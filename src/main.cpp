#include "MRayTracer.h"
#include "MSphere.h"
#include "MPlane.h"
#include "MBox.h"
#include "MSmartPointer.h"

#include <iostream>
#include <fstream>
#include <ctime>

static void imgToPbm(const MImage& img)
{
    std::ofstream f("output.pbm");
    f << "P3" << std::endl;
    f << img.width() << " " << img.height() << std::endl;
    f << "255" << std::endl;

    for (auto y = 0; y < img.height(); ++y)
    {
        for (auto x = 0; x < img.width(); ++x)
        {
            const MColor pixelColor = img.get(x, y);
            f << std::to_string((int)(pixelColor.x)) << " " << std::to_string((int)(pixelColor.y)) << " " << std::to_string(int(pixelColor.z));
            if (x + 1 < img.width())
            {
                f << " ";
            }
        }
        f << std::endl;
    }
    f.flush();
}

int main(int argc, char *argv[])
{
    std::srand(std::time(nullptr));

    MColor::record("Turquoise", MColor(64, 224, 208));
    MColor::record("Marron", MColor(94, 61, 50));
    MColor::record("Khaki", MColor(0, 57, 0));
    MColor::record("Burgundy", MColor(120, 10, 10));

    MRayTracer tracer;
    tracer.supersampling = MRayTracer::MSuperSamplingMode::X4;

    // config camera
    tracer.scene.camera.position = MVector(0.0, 500.0, 0.0);
    tracer.scene.camera.orientation = MVector(180.0, 0.0, 0.0);
    tracer.scene.camera.FOVHorizontal = 30.0;
    tracer.scene.camera.FOVVertical = 30.0;
    
    // config window
    tracer.scene.window.width = 500;
    tracer.scene.window.height = 500;
    
    // config objects

    // floor
    MSmartPointer<MPlane> pln1 = new MPlane(MVector(0.0, 0.0, -100.0), MVector(0.0, 0.0, 0.0));
    pln1->material = MMaterial::Plain();
    pln1->material.dColor = MColor::black();
    pln1->material.sColor = MColor::black();
    pln1->texture = MTexture::Checker(10.0);
    tracer.scene.objects.emplace_back(pln1);

    // ceil
    MSmartPointer<MPlane> pln2 = new MPlane(MVector(0.0, 0.0, 100.0), MVector(0.0, 180.0, 0.0));
    pln2->material = MMaterial::Random();
    std::cout << pln2->material.toStringDebug() << std::endl;
    //pln2->material.dColor = MColor::white();
    //pln2->material.sColor = MColor::white();
    tracer.scene.objects.emplace_back(pln2);

    // left
    MSmartPointer<MPlane> pln3 = new MPlane(MVector(100.0, 0.0, 0.0), MVector(0.0, 0.0, -90.0));
    pln3->material = MMaterial::Plain();
    pln3->material.dColor = MColor::get("Khaki");
    pln3->material.sColor = MColor::get("Khaki");
    pln3->texture = MTexture::Camo(10.0);
    tracer.scene.objects.emplace_back(pln3);
    
    // right
    MSmartPointer<MPlane> pln4 = new MPlane(MVector(-100.0, 0.0, 0.0), MVector(0.0, 0.0, 90.0));
    pln4->material = MMaterial::Plain();
    pln4->material.dColor = MColor::get("Marron");
    pln4->material.sColor = MColor::get("Marron");
    pln4->texture = MTexture::Wood(50.0);
    tracer.scene.objects.emplace_back(pln4);
    
    // back
    MSmartPointer<MPlane> pln5 = new MPlane(MVector(0.0, -100.0, 0.0), MVector(0.0, -90.0, 0.0));
    pln5->material = MMaterial::Metal();
    pln5->material.dColor = MColor::blue();
    tracer.scene.objects.emplace_back(pln5);

    MSmartPointer<MSphere> sph1 = new MSphere(MVector(-40.0, -50.0, 0.0), MVector(0.0, 0.0, 0.0), 40.0);
    sph1->material = MMaterial::Glossy();
    sph1->material.dColor = MColor::get("Burgundy");
    sph1->material.sColor = MColor::get("Burgundy");
    sph1->texture = MTexture::Checker(4.0);
    tracer.scene.objects.emplace_back(sph1);

    // sphere plastic
    //MSmartPointer<MSphere> sph1 = new MSphere(MVector(-50.0, 0.0, 0.0), MVector::zero(), 40.0);
    //sph1->material = MMaterial::Plastic();
    //tracer.scene.objects.emplace_back(sph1);
    
    // sphere metal
    //MSmartPointer<MSphere> sph2 = new MSphere(MVector(50.0, 60.0, 0.0), MVector::zero(), 30.0);
    //sph2->material = MMaterial::Metal();
    //tracer.scene.objects.emplace_back(sph2);
    
    // sphere mirror
    MSmartPointer<MSphere> sph3 = new MSphere(MVector(40.0, -50.0, 00.0), MVector::zero(), 20.0);
    sph3->material = MMaterial::Mirror();
    tracer.scene.objects.emplace_back(sph3);
    
    // sphere water
    MSmartPointer<MSphere> sph4 = new MSphere(MVector(0.0, 250.0, -30.0), MVector::zero(), 20.0);
    sph4->material = MMaterial::Water();
    tracer.scene.objects.emplace_back(sph4);

    //MSmartPointer<MSphere> sph5 = new MSphere(MVector(0.0, 00.0, 0.0), MVector::zero(), 50.0);
    //sph5->material = MMaterial::Metal();
    //sph5->material.dColor = MColor::get("Marron");
    //sph5->material.sColor = MColor::get("Marron");
    //sph5->texture = MTexture::Marble(2.0);
    //tracer.scene.objects.emplace_back(sph5);

    // box
    //MSmartPointer<MBox> box1 = new MBox(MVector(0.0, 250.0, -30.0), MVector(45.0, 45.0, 45.0), MVector(15.0, 15.0, 15.0));
    //box1->material.dColor = MColor::green();
    //box1->material.aK = 0.1;
    //box1->material.dK = 0.4;
    //box1->material.sColor = MColor::green();
    //box1->material.sK = 0.2;
    //box1->material.shininess = 2.0;
    //box1->material.reflectivity = 0.0;
    //box1->material.rGlossiness = 0.0;
    //box1->material.transparency = 0.0;
    //box1->material.tGlossiness = 0.0;
    //box1->material.tI = 1.0;
    //box1->texture = MTexture::Camo(4.0);
    //tracer.scene.objects.emplace_back(box1);

    // config lights
    MSmartPointer<MLight> lgh1 = new MLight(MVector(0.0, 95.0, 55.0), MVector::zero(), 1.0);
    tracer.scene.lights.emplace_back(lgh1);

    MSmartPointer<MLight> lgh2 = new MLight(MVector(-50.0, 75.0, 55.0), MVector::zero(), 1.0);
    tracer.scene.lights.emplace_back(lgh2);

    // render frame
    MImage image = tracer.render();
    imgToPbm(image);

    return 0;
}