#include <vtkVersion.h>
#include <vtkPlaneSource.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
 #include<iostream>

#include "log\cout_log.h"
#include "log\log_helper_functions.h"

int main(int, char *[]){
	nut::CoutLog log;

	// Create a plane
	nut::SecureLog(&log,"Create a plane");
	vtkSmartPointer<vtkPlaneSource> planeSource = vtkSmartPointer<vtkPlaneSource>::New();
	planeSource->SetCenter(1.0, 0.0, 0.0);
	planeSource->SetNormal(1.0, 0.0, 1.0);
	nut::SecureLogValue(&log,"Class name",planeSource->GetClassName());
	planeSource->Update();

	// Create a sphere
	nut::SecureLog(&log,"Create a sphere");
	vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetCenter(1.0, 0.15, 0.0);
	sphereSource->SetRadius(0.25);
	sphereSource->SetThetaResolution(20);
	sphereSource->SetPhiResolution(20);
	nut::SecureLogValue(&log,"Class name",sphereSource->GetClassName());
	sphereSource->Update();

	
	//vtkPolyData: concrete dataset represents vertices, lines, polygons, and triangle strips
	//vtkPolyData is a data object that is a concrete implementation of vtkDataSet. vtkPolyData represents a geometric structure 
	//consisting of vertices, lines, polygons, and/or triangle strips. Point and cell attribute values (e.g., scalars, vectors, etc.) 
	//also are represented.
	vtkPolyData* plane	= planeSource->GetOutput();
	vtkPolyData* sphere	= sphereSource->GetOutput();

	// Create a mapper and actor
	nut::SecureLog(&log,"Create a couple of mappers and actors");
	vtkSmartPointer<vtkPolyDataMapper> planeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	planeMapper->SetInputData(plane);
	vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper->SetInputData(sphere);

	vtkSmartPointer<vtkActor> planeActor = vtkSmartPointer<vtkActor>::New();
	planeActor->SetMapper(planeMapper);
	vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
	sphereActor->SetMapper(sphereMapper);

	// Create a renderer, render window and interactor
	nut::SecureLog(&log,"Create a renderer, render window and interactor");
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	// Add the actors to the scene
	nut::SecureLog(&log,"Add the actors to the scene");
	renderer->AddActor(planeActor);
	renderer->AddActor(sphereActor);
	renderer->SetBackground(0,.5,0.9); // Background color dark blue

	// Render and interact
	nut::SecureLog(&log,"Render and interact");
	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}