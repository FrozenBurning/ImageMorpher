#include "include/distortion.h"

cv::Point2d plate2sphere(cv::Point2d point_on_plate, double radius, cv::Point2d centre,double distort_k)
{
    cv::Point2d point_on_sphere, gap;
    gap = (point_on_plate - centre)/radius;
    double distance = sqrt(gap.x * gap.x + gap.y * gap.y);

    double newx = gap.x*(1+distort_k*distance*distance);
    double newy = gap.y*(1+distort_k*distance*distance);

    point_on_sphere = cv::Point2d(newx,newy)*radius+centre;
    // point_on_plate.x = gap.x * (2 * radius / (M_PI * distance) * asin(distance / radius));
    // point_on_plate.y = gap.y * (2 * radius / (M_PI * distance) * asin(distance / radius));

    // //transform to pixel coordination
    // point_on_plate = point_on_plate + centre;
    if(point_on_sphere.x > centre.x*2 || point_on_sphere.y > centre.y*2 || point_on_sphere.x < 0 || point_on_sphere.y < 0)
    {
        point_on_sphere.x = -1;
        point_on_sphere.y = -1;
    }
    if (isnan(point_on_sphere.x) || isnan(point_on_sphere.y))
    {
        point_on_sphere.x = point_on_plate.x;
        point_on_sphere.y = point_on_plate.y;
    }

    return point_on_sphere;
}


cv::Point2d distort_trans(cv::Point2d &p, double max_rotation, double radius,cv::Point2d centre)
{
    cv::Point2d gap;
    gap = p - centre;
    double distance = sqrt(gap.x * gap.x + gap.y * gap.y);
    if (distance > radius)
        return cv::Point2d(p.x, p.y);
    double rotation = max_rotation * (radius - distance) / radius;

    double newx = (p.x - centre.x) * cos(rotation) - (p.y - centre.y) * sin(rotation) + centre.x;
    double newy = (p.x - centre.x) * sin(rotation) + (p.y - centre.y) * cos(rotation) + centre.y;
    return cv::Point2d(newx, newy);
}
