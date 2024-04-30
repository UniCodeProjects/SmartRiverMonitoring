#ifndef SONAR_H
#define SONAR_H

/// @brief Class that represents a generic sonar.
class Sonar {
   public:
    /// @brief Retrieves the distance in meters from the nearest object.
    /// @return the distance in meters from the nearest object
    virtual double getDistance();
};

#endif
