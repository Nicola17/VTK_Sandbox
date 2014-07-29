#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkPointPicker.h>
#include <vtkCamera.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>
#include <vtkProperty.h>
#include <vtkPointPicker.h>
#include <vtkPropPicker.h>
#include <vtkMath.h>
#include <vtkInteractorStyleRubberBandZoom.h>

#include "log\cout_log.h"
#include "log\log_helper_functions.h"

// Define interaction style
class MyMouseInteractorStyle : public vtkInteractorStyleTrackballCamera
{
  public:
    static MyMouseInteractorStyle* New();
    vtkTypeMacro(MyMouseInteractorStyle, vtkInteractorStyleTrackballCamera);

	MyMouseInteractorStyle():last_picked_actor_(nullptr),last_picked_property_(nullptr),_log(nullptr){
		last_picked_property_ = vtkSmartPointer<vtkProperty>::New();
	}
 
    virtual void OnLeftButtonDown() 
    {
	  nut::SecureLog(_log,"Pressed left mouse button.");
	  nut::SecureLog(_log,"Picking pixel");
	  nut::SecureLogValue(_log,"x", this->Interactor->GetEventPosition()[0]);
	  nut::SecureLogValue(_log,"y", this->Interactor->GetEventPosition()[1]);
      this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0], 
                         this->Interactor->GetEventPosition()[1], 
                         0,  // always zero.
                         this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
      double picked[3];
      this->Interactor->GetPicker()->GetPickPosition(picked);
	  nut::SecureLog(_log,"Data position");
      nut::SecureLogValue(_log,"x", picked[0]);
	  nut::SecureLogValue(_log,"y", picked[1]);
	  nut::SecureLogValue(_log,"z", picked[2]);

      // Forward events
      vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }
 
    virtual void OnMiddleButtonDown(){
	  nut::SecureLog(_log,"Pressed middle mouse button.");
      // Forward events
      vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
    }
 
    virtual void OnRightButtonDown(){
	  nut::SecureLog(_log,"Pressed right mouse button.");
      // Forward events
      vtkInteractorStyleTrackballCamera::OnRightButtonDown();
    }

	virtual void OnKeyPress(){
		// Get the keypress
		vtkRenderWindowInteractor *rwi = this->Interactor;
		std::string key = rwi->GetKeySym();
		nut::SecureLogValue(_log,"Key pressed", key);
 
		if(key.compare("9") == 0){
			selectActor();
		}
		if(key.compare("8") == 0){
			unselectActor();
		}

		// Forward events
		vtkInteractorStyleTrackballCamera::OnKeyPress();
    }

private:
	void selectActor(){
		nut::SecureLog(_log,"Selecting an actor.");
		int* clickPos = this->GetInteractor()->GetEventPosition();
		nut::SecureLog(_log,"Picking pixel");
		nut::SecureLogValue(_log,"x", clickPos[0]);
		nut::SecureLogValue(_log,"y", clickPos[1]);
 
		// Pick from this location.
		vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
		picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());
		
		double* pos = picker->GetPickPosition();
		
		// If we picked something before, reset its property
		if (last_picked_actor_){
			last_picked_actor_->GetProperty()->DeepCopy(last_picked_property_);
		}
		last_picked_actor_ = picker->GetActor();
		
		if (last_picked_actor_){
			// Save the property of the picked actor so that we can
			// restore it next time
			last_picked_property_->DeepCopy(last_picked_actor_->GetProperty());
			// Highlight the picked actor by changing its properties
			last_picked_actor_->GetProperty()->SetDiffuseColor(1.0, 0.0, 0.0);
		}
		Interactor->Render();
	}

	void unselectActor(){
		if (last_picked_actor_){
			nut::SecureLog(_log,"Unselecting the selected actor.");
			last_picked_actor_->GetProperty()->DeepCopy(last_picked_property_);
			last_picked_actor_ = nullptr;
			Interactor->Render();
		}else{
			nut::SecureLog(_log,"There's no actor selected.");
		}
	}
 
public:
	nut::AbstractLog* _log;

private:
	vtkActor* last_picked_actor_;
	vtkSmartPointer<vtkProperty> last_picked_property_;
};
 
vtkStandardNewMacro(MyMouseInteractorStyle);

int main(int, char *[])
{
	nut::CoutLog log;
	int numberOfSpheres = 10;
 
	// A renderer and render window
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer ( renderer );
 
	// An interactor
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow ( renderWindow );
 
	// Set the custom type to use for interaction.
	vtkSmartPointer<MyMouseInteractorStyle> style = vtkSmartPointer<MyMouseInteractorStyle>::New();
	style->SetDefaultRenderer(renderer);
	style->_log = &log;
 
	renderWindowInteractor->SetInteractorStyle( style );
 
	for (int i = 0; i < numberOfSpheres; ++i){
		vtkSmartPointer<vtkSphereSource> source = vtkSmartPointer<vtkSphereSource>::New();
		double x, y, z, radius;
		x = vtkMath::Random(-5,5);
		y = vtkMath::Random(-5,5);
		z = vtkMath::Random(-5,5);
		radius = vtkMath::Random(.5, 1.0);
		source->SetRadius(radius);
		source->SetCenter(x, y, z);
		source->SetPhiResolution(21);
		source->SetThetaResolution(31);
		vtkSmartPointer<vtkPolyDataMapper> mapper =	vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection ( source->GetOutputPort());
		vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
		actor->SetMapper ( mapper );
		double r, g, b;
		r = vtkMath::Random(.4, 1.0);
		g = vtkMath::Random(.4, 1.0);
		b = vtkMath::Random(.4, 1.0);
		actor->GetProperty()->SetDiffuseColor(r, g, b);
		actor->GetProperty()->SetDiffuse(.8);
		actor->GetProperty()->SetSpecular(.5);
		actor->GetProperty()->SetSpecularColor(1.0,1.0,1.0);
		actor->GetProperty()->SetSpecularPower(30.0);
		renderer->AddActor ( actor );
	}
 
	renderer->GradientBackgroundOn();
	renderer->SetBackground(0.1,0.1,0.1);
	renderer->SetBackground2(0.9,0.5,0);
 
	// Render and interact
	renderWindow->Render();
	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();
 
	return EXIT_SUCCESS;
}