// Declarations
#include "vicon_visualizer/visualization.h"

// Vicon tools
#include "vicon_tools/ros_object.h"				// vicon_tools::ros_object

// Initializes the namespace
void Visualization::init()
{
	// Set up publisher
	ros::NodeHandle n;
	marker_pub = n.advertise<visualization_msgs::Marker>("object_marker", 1);
}


// Creates a marker
visualization_msgs::Marker Visualization::createMarker(const vicon_tools::ros_object object)
{
	visualization_msgs::Marker marker;			// Marker object

	// Set default settings
	setDefaultMarkerSettings(&marker);

	// Set timestamp and id
	marker.header.stamp = ros::Time::now();
	marker.id = 0;

	// Set coordinates
	marker.pose.position.x = object.x;
	marker.pose.position.y = object.y;
	marker.pose.position.z = object.z;

	// Set normalized quaternion
	double norm = sqrt(object.rx * object.rx + object.ry * object.ry + object.rz * object.rz + 1);
	marker.pose.orientation.x = object.rx / norm;
	marker.pose.orientation.y = object.ry / norm;
	marker.pose.orientation.z = object.rz / norm;
	marker.pose.orientation.w = 1.0 / norm;

	// Set lifetime
	marker.lifetime = ros::Duration();

	// Return marker
	return marker;
}

// Creates a marker that removes it from the visualizer
visualization_msgs::Marker Visualization::createRemovalMarker(std::string name)
{
	visualization_msgs::Marker marker;			// Marker object

/*	// Set id
	marker.id = id;

	// Set up removal
	marker.header.frame_id = "/object_frame";			// Attach to general object_frame	
	marker.ns = "objects";								// Marker lives in the objects namespace
	marker.action = visualization_msgs::Marker::DELETE;
*/
	return marker;
}

// Handle for when a remove message has arrived
void Visualization::onObjectRemove(const vicon_tools::remove_objects::ConstPtr& msg)
{
	visualization_msgs::Marker marker;			// Holds marker to remove

	// For each ID
	for (int i = 0; i < msg->names.size(); i++)
	{
		// Create marker
		marker = createRemovalMarker(msg->names[i]);

		// Publish ball marker
		marker_pub.publish(marker);
	}
}

// Handle for when an update message has arrived
void Visualization::onObjectUpdate(const vicon_tools::ros_object_array::ConstPtr& msg)
{
	visualization_msgs::Marker marker;			// Holds marker to send

	// For each object
	for (int i = 0; i < msg->objects.size(); i++)
	{std::cout << "X: " << msg->objects[i].x << std::endl;
		// Create marker
		marker = createMarker(msg->objects[i]);

		// Publish ball marker
		marker_pub.publish(marker);
	}
}

// Set the default marker
void Visualization::setDefaultMarkerSettings(visualization_msgs::Marker* marker)
{
	// Set default info
	marker->header.frame_id = "/object_frame";			// Attach to general object_frame
	marker->ns = "objects";								// Marker lives in the objects namespace
	marker->type = visualization_msgs::Marker::SPHERE;	// Set marker to sphere
	marker->action = visualization_msgs::Marker::ADD;	// Add (update) marker

	// Set default scale
	marker->scale.x = BALL_SIZE;
	marker->scale.y = BALL_SIZE;
	marker->scale.z = BALL_SIZE;

	// Set default color
	marker->color.r = 0.0f;
	marker->color.g = 1.0f;
	marker->color.b = 0.0f;
	marker->color.a = 1.0;
}

// Terminates the namespace
void Visualization::terminate()
{
	// Shutdown publisher
	marker_pub.shutdown();
}