#include <vtkSmartPointer.h>
#include <vtkQuadric.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkSphereSource.h>
 
#include "log\cout_log.h"
#include "log\log_helper_functions.h"

int main(int, char *[]){

	nut::CoutLog log;
	// Create the quadric function definition
	vtkSmartPointer<vtkQuadric> quadric = vtkSmartPointer<vtkQuadric>::New();
	nut::SecureLogValue(&log,"Quadric",quadric->GetClassName());
	quadric->SetCoefficients(.5,1,.2,0,.1,0,0,.2,0,0);
 
	// Sample the quadric function
	vtkSmartPointer<vtkSampleFunction> sample = vtkSmartPointer<vtkSampleFunction>::New();
	nut::SecureLogValue(&log,"Sample",sample->GetClassName());
	sample->SetSampleDimensions(50,50,50);
	sample->SetImplicitFunction(quadric);
	double xmin = 0, xmax=1, ymin=0, ymax=1, zmin=0, zmax=1;
	sample->SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax);
 
	vtkSmartPointer<vtkContourFilter> contourFilter = vtkSmartPointer<vtkContourFilter>::New();
	nut::SecureLogValue(&log,"Contour filter",contourFilter->GetClassName());
	contourFilter->SetInputConnection(sample->GetOutputPort());
	contourFilter->GenerateValues(1, 1.0, 1.0);
	contourFilter->Update();
 
	// Visualize
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	nut::SecureLogValue(&log,"Mapper",mapper->GetClassName());
	mapper->SetInputConnection(contourFilter->GetOutputPort());
 
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	nut::SecureLogValue(&log,"Actor",actor->GetClassName());
	mapper->ScalarVisibilityOff(); //!
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(0,0.4,0.7);
	actor->GetProperty()->SetInterpolationToFlat();
	actor->GetProperty()->SetOpacity(0.6);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);
 
	renderer->AddActor(actor);
	renderer->GradientBackgroundOn();
	renderer->SetBackground(0.1,0.1,0.1);
	renderer->SetBackground2(0.9,0.5,0);

	renderWindow->Render();
	renderWindowInteractor->Start();	

	return EXIT_SUCCESS;
}
