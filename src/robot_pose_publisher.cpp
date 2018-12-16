#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_listener.h>

class RobotPose
{
  public:
    RobotPose(): nh_("~")
    {
      pose_pub_ = nh_.advertise<geometry_msgs::PoseStamped>("/erlc/robot_pose",1);
    }

    void step()
    {
      tf::StampedTransform map2bf;
      geometry_msgs::PoseStamped pose;
      try
      {
        tf_listener_.waitForTransform("/map", "/base_footprint",ros::Time(0), ros::Duration(0.5));
        tf_listener_.lookupTransform("/map", "/base_footprint", ros::Time(0), map2bf);
        tf::quaternionTFToMsg(map2bf.getRotation(), pose.pose.orientation);
        tf::quaternionTFToMsg(map2bf.getRotation(), pose.pose.orientation);
        pose.pose.position.x = map2bf.getOrigin().getX();
        pose.pose.position.y = map2bf.getOrigin().getY();
        pose.pose.position.z = 0.0;
        pose.header.frame_id = "map";
        pose.header.stamp = ros::Time::now();
        pose_pub_.publish(pose);
      }
      catch(tf::TransformException& ex){}
    }

  private:
    ros::NodeHandle nh_;
    ros::Publisher pose_pub_;
    tf::TransformListener tf_listener_;
  };

int main(int argc, char** argv)
{
    ros::init(argc, argv, "robot_pose_publisher");
    RobotPose robot_pose;
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
      robot_pose.step();
      ros::spinOnce();
      loop_rate.sleep();
    }
    return 0;
}
