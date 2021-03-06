#ifndef VICON_VISUALIZER_VICON_VISUALIZER_H
#define VICON_VISUALIZER_VICON_VISUALIZER_H

// Qt
#include <QWidget>														// QWidget

// ROS
#include "ros/ros.h"													// ros::*

// RViz
#include "rviz/display.h"												// rviz::Display
#include "rviz/default_plugin/view_controllers/orbit_view_controller.h"	// rviz::OrbitViewController

// Vicon visualizer
#include "vicon_visualizer/ui_vicon_visualizer.h"						// Ui::ViconVisualizer

class ViconVisualizer : public QWidget
{
	Q_OBJECT

	public:
		// Constructor
		ViconVisualizer(QWidget* parent);

		// Destructor
		~ViconVisualizer();

	private:
		bool isAcceptingMarkers_;						// Holds whether the marker dispaly is accepting marker messages
		rviz::Display* markers_;						// Marker display
		ros::Subscriber object_sub_;     				// Subscriber to object_update
		ros::Subscriber remove_sub_;     				// Subscriber to object_remove
		Ui::ViconVisualizer	ui_;						// Ui::ViconVisualizer


	private slots:
		/* Button slots */

		// Fires when the pause button is pressed
		void pauseButtonPressed();

		// Fires when the reset button is pressed
		void resetButtonPressed();

		/* Combo box slot */

		// Fires when shape combo box has changed
		void shapeComboCurrentIndexChanged(int index);

		/* Edit box slots */

		// Fires when X scale editiing is finished
		void scaleXEditingFinished();

		// Fires when Y scale editiing is finished
		void scaleYEditingFinished();

		// Fires when Z scale editiing is finished
		void scaleZEditingFinished();
};

#endif  // VICON_VISUALIZER_VICON_VISUALIZER_H
