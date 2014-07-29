#include <vtkVersion.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
 #include<iostream>

#include "log\cout_log.h"
#include "log\log_helper_functions.h"

int main(int, char *[]){
	nut::CoutLog log;

	// Create a sphere
	nut::SecureLog(&log,"Create a sphere");
	vtkSmartPointer<vtkSphereSource> sphereSource0 = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource0->SetCenter(0.0, 0.15, 0.0);
	sphereSource0->SetRadius(0.5);
	sphereSource0->SetThetaResolution(20);
	sphereSource0->SetPhiResolution(20);
	nut::SecureLogValue(&log,"Class name",sphereSource0->GetClassName());
	sphereSource0->Update();
	vtkPolyData* sphere0	= sphereSource0->GetOutput();
	vtkSmartPointer<vtkPolyDataMapper> sphereMapper0 = vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper0->SetInputData(sphere0);
	vtkSmartPointer<vtkActor> sphereActor0 = vtkSmartPointer<vtkActor>::New();
	sphereActor0->SetMapper(sphereMapper0);

	// Create a sphere
	nut::SecureLog(&log,"Create a sphere");
	vtkSmartPointer<vtkSphereSource> sphereSource1 = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource1->SetCenter(1.0, 0.15, 0.0);
	sphereSource1->SetRadius(0.25);
	sphereSource1->SetThetaResolution(20);
	sphereSource1->SetPhiResolution(20);
	nut::SecureLogValue(&log,"Class name",sphereSource1->GetClassName());
	sphereSource1->Update();
	vtkPolyData* sphere1	= sphereSource1->GetOutput();
	vtkSmartPointer<vtkPolyDataMapper> sphereMapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper1->SetInputData(sphere1);
	vtkSmartPointer<vtkActor> sphereActor1 = vtkSmartPointer<vtkActor>::New();
	sphereActor1->SetMapper(sphereMapper1);
	
	// Create a sphere
	nut::SecureLog(&log,"Create a sphere");
	vtkSmartPointer<vtkSphereSource> sphereSource2 = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource2->SetCenter(1.0, 0.75, 0.0);
	sphereSource2->SetRadius(0.25);
	sphereSource2->SetThetaResolution(20);
	sphereSource2->SetPhiResolution(20);
	nut::SecureLogValue(&log,"Class name",sphereSource2->GetClassName());
	sphereSource2->Update();
	vtkPolyData* sphere2	= sphereSource2->GetOutput();
	vtkSmartPointer<vtkPolyDataMapper> sphereMapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper2->SetInputData(sphere2);
	vtkSmartPointer<vtkActor> sphereActor2 = vtkSmartPointer<vtkActor>::New();
	sphereActor2->SetMapper(sphereMapper2);

	
	// Create a sphere
	nut::SecureLog(&log,"Create a sphere");
	vtkSmartPointer<vtkSphereSource> sphereSource3 = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource3->SetCenter(2.0, 0.75, 0.0);
	sphereSource3->SetRadius(0.25);
	sphereSource3->SetThetaResolution(20);
	sphereSource3->SetPhiResolution(20);
	nut::SecureLogValue(&log,"Class name",sphereSource3->GetClassName());
	sphereSource3->Update();
	vtkPolyData* sphere3	= sphereSource3->GetOutput();
	vtkSmartPointer<vtkPolyDataMapper> sphereMapper3 = vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper3->SetInputData(sphere3);
	vtkSmartPointer<vtkActor> sphereActor3 = vtkSmartPointer<vtkActor>::New();
	sphereActor3->SetMapper(sphereMapper3);


	// Create a sphere
	nut::SecureLog(&log,"Create a sphere");
	vtkSmartPointer<vtkSphereSource> sphereSource4 = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource4->SetCenter(2.0, 0.15, 0.0);
	sphereSource4->SetRadius(0.25);
	sphereSource4->SetThetaResolution(20);
	sphereSource4->SetPhiResolution(20);
	nut::SecureLogValue(&log,"Class name",sphereSource4->GetClassName());
	sphereSource4->Update();
	vtkPolyData* sphere4	= sphereSource4->GetOutput();
	vtkSmartPointer<vtkPolyDataMapper> sphereMapper4 = vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper4->SetInputData(sphere4);
	vtkSmartPointer<vtkActor> sphereActor4 = vtkSmartPointer<vtkActor>::New();
	sphereActor4->SetMapper(sphereMapper4);

/******************************************************************************/

	nut::SecureLog(&log,"Let's try some different shading/color options");
	sphereActor0->GetProperty()->SetInterpolationToFlat();
	sphereActor0->GetProperty()->SetEdgeColor(0.25,0.05,0.05); //(R,G,B)
	sphereActor0->GetProperty()->EdgeVisibilityOn();
	sphereActor0->GetProperty()->SetColor(0.5,0.1,0.1);


	sphereActor1->GetProperty()->SetInterpolationToGouraud();
	sphereActor1->GetProperty()->SetColor(0.0,0.4,0.7);

	sphereActor2->GetProperty()->SetInterpolationToPhong();
	sphereActor2->GetProperty()->SetColor(0.0,0.4,0.7);

	sphereActor3->GetProperty()->SetInterpolationToPhong();
	sphereActor3->GetProperty()->SetColor(0.4,0.7,0.0);
	sphereActor3->GetProperty()->SetOpacity(0.3);

	sphereActor4->GetProperty()->SetInterpolationToPhong();
	sphereActor4->GetProperty()->SetColor(0.4,0.7,0.0);
	sphereActor4->GetProperty()->SetRepresentationToWireframe();



	// Create a renderer, render window and interactor
	nut::SecureLog(&log,"Create a renderer, render window and interactor");
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	// Add the actors to the scene
	nut::SecureLog(&log,"Add the actors to the scene");
	renderer->AddActor(sphereActor0);
	renderer->AddActor(sphereActor1);
	renderer->AddActor(sphereActor2);
	renderer->AddActor(sphereActor3);
	renderer->AddActor(sphereActor4);

	nut::SecureLog(&log,"Create a background with a gradient");
	renderer->GradientBackgroundOn();
	renderer->SetBackground(0.1,0.1,0.1);
	renderer->SetBackground2(0.9,0.5,0);

	// Render and interact
	nut::SecureLog(&log,"Render and interact");
	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}