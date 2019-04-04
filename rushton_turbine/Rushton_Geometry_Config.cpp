//
//  Header.h
//  TD_GeomInput_Rushton_Turbine
//
//  Created by Nile Ó Broin on 13/02/2019.
//  Copyright © 2019 Nile Ó Broin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cmath>

#include "json.h"

#include "Rushton_Geometry_Config.hpp"







void GeometryConfig::setGeometryConfig(tNi gridx, tGeomShape uav)
{
    resolution = 0.7f;


    //diameter tube / cylinder
    tankDiameter = tGeomShape(gridx - MDIAM_BORDER);

    shaft.radius = tankDiameter * 2.0f / 75.0f;



    baffles.numBaffles = 4;

    //First baffle is offset by 1/8 of revolution, or 1/2 of the delta between baffles.
    baffles.firstBaffleOffset = (tGeomShape)(((2.0 * M_PI) / (tGeomShape)baffles.numBaffles) * 0.5);

    baffles.innerRadius = 0.3830f * tankDiameter;
    baffles.outerRadius = 0.4830f * tankDiameter;
    baffles.thickness = tankDiameter / 75.0f;


    numImpellers = 1;


    impeller0.impeller_position = tGeomShape(gridx) * (2.0f / 3.0f); //center x direction

    impeller0.numBlades = 6;

    impeller0.firstBladeOffset = 0.0f;


    impeller0.blades.innerRadius = tankDiameter / 12.0f;
    impeller0.blades.outerRadius = tankDiameter / 6.0f;

    // bottom height impeller blade
    impeller0.blades.top = tankDiameter * 19.0f / 30.f;
    impeller0.blades.bottom = tankDiameter * 21.0f / 30.f;


    // top height impeller blade
    impeller0.blades.bladeThickness = tankDiameter / 75.0f;


    impeller0.uav = uav;

    // Eventual angular velocity impeller
    impeller0.blade_tip_angular_vel_w0 = impeller0.uav / impeller0.blades.outerRadius;



    impeller0.disk.radius = tankDiameter / 8.0f;
    impeller0.disk.top = tankDiameter * 99.0f / 150.0f;
    impeller0.disk.bottom = tankDiameter * 101.0f / 150.0f;

    impeller0.hub.radius = tankDiameter * 4.0f / 75.0f;
    impeller0.hub.top = tankDiameter * 19.f / 30.0f;
    impeller0.hub.bottom = tankDiameter * 21.0f / 30.0f;



};



void GeometryConfig::setGeometryStartup(tStep starting_step, tGeomShape impeller_start_angle,
                                        tStep impeller_startup_steps_until_normal_speed){

    starting_step = starting_step;
    impeller_start_angle = impeller_start_angle;
    impeller_startup_steps_until_normal_speed = impeller_startup_steps_until_normal_speed;

}






void GeometryConfig::loadGeometryConfigAsJSON(std::string filepath){


    try
    {
        std::ifstream in(filepath.c_str());
        Json::Value dim_json;
        in >> dim_json;


        resolution = (tGeomShape)dim_json["resolution"].asDouble();
        tankDiameter = (tGeomShape)dim_json["tankDiameter"].asDouble();


        starting_step = (tStep)dim_json["starting_step"].asInt();
        impeller_start_angle = (tGeomShape)dim_json["impeller_start_angle"].asDouble();
        impeller_startup_steps_until_normal_speed = (tStep)dim_json["impeller_startup_steps_until_normal_speed"].asInt();



        baffles.numBaffles = (int)dim_json["baffles"]["numBaffles"].asInt();
        baffles.firstBaffleOffset = (tGeomShape)dim_json["baffles"]["firstBaffleOffset"].asDouble();
        baffles.innerRadius = (tGeomShape)dim_json["baffles"]["innerRadius"].asDouble();
        baffles.outerRadius = (tGeomShape)dim_json["baffles"]["outerRadius"].asDouble();
        baffles.thickness = (tGeomShape)dim_json["baffles"]["thickness"].asDouble();


        numImpellers = (int)dim_json["numImpellers"].asInt();


        impeller0.firstBladeOffset = (tGeomShape)dim_json["impeller0"]["firstBladeOffset"].asDouble();
        impeller0.uav = (tGeomShape)dim_json["impeller0"]["uav"].asDouble();
        impeller0.blade_tip_angular_vel_w0 = (tGeomShape)dim_json["impeller0"]["blade_tip_angular_vel_w0"].asDouble();
        impeller0.impeller_position = (tGeomShape)dim_json["impeller0"]["impeller_position"].asDouble();



        impeller0.blades.innerRadius = (tGeomShape)dim_json["impeller0"]["blades"]["innerRadius"].asDouble();
        impeller0.blades.outerRadius = (tGeomShape)dim_json["impeller0"]["blades"]["outerRadius"].asDouble();
        impeller0.blades.bottom = (tGeomShape)dim_json["impeller0"]["blades"]["bottom"].asDouble();
        impeller0.blades.top = (tGeomShape)dim_json["impeller0"]["blades"]["top"].asDouble();
        impeller0.blades.bladeThickness = (tGeomShape)dim_json["impeller0"]["blades"]["bladeThickness"].asDouble();

        impeller0.disk.radius = (tGeomShape)dim_json["impeller0"]["disk"]["radius"].asDouble();
        impeller0.disk.bottom = (tGeomShape)dim_json["impeller0"]["disk"]["bottom"].asDouble();
        impeller0.disk.top = (tGeomShape)dim_json["impeller0"]["disk"]["top"].asDouble();

        impeller0.hub.radius = (tGeomShape)dim_json["impeller0"]["hub"]["radius"].asDouble();
        impeller0.hub.bottom = (tGeomShape)dim_json["impeller0"]["hub"]["bottom"].asDouble();
        impeller0.hub.top = (tGeomShape)dim_json["impeller0"]["hub"]["top"].asDouble();


        in.close();

    }
    catch(std::exception& e)
    {
        std::cerr << "Unhandled Exception reached parsing arguments: "
        << e.what() << ", application will now exit" << std::endl;
    }


}




int GeometryConfig::saveGeometryConfigAsJSON(std::string filepath){

    try
    {

        Json::Value dim_json;


        dim_json["name"] = "GeometryConfig";

        dim_json["function"] = "saveGeometryConfigAsJSON";

        dim_json["gridx"] = (double)(tankDiameter + MDIAM_BORDER);

        dim_json["resolution"] = (double)resolution;
        dim_json["tankDiameter"] = (double)tankDiameter;


        dim_json["starting_step"] = starting_step;
        dim_json["impeller_start_angle"] = (double)impeller_start_angle;
        dim_json["impeller_startup_steps_until_normal_speed"] = impeller_startup_steps_until_normal_speed;



        dim_json["baffles"]["numBaffles"] = (int)baffles.numBaffles;
        dim_json["baffles"]["firstBaffleOffset"] = (double)baffles.firstBaffleOffset;
        dim_json["baffles"]["innerRadius"] = (double)baffles.innerRadius;
        dim_json["baffles"]["outerRadius"] = (double)baffles.outerRadius;
        dim_json["baffles"]["thickness"] = (double)baffles.thickness;




        dim_json["numImpellers"] = (int)numImpellers;


        dim_json["impeller0"]["firstBladeOffset"] = (double)impeller0.firstBladeOffset;
        dim_json["impeller0"]["uav"] = (double)impeller0.uav;
        dim_json["impeller0"]["blade_tip_angular_vel_w0"] = (double)impeller0.blade_tip_angular_vel_w0;
        dim_json["impeller0"]["impeller_position"] = (double)impeller0.impeller_position;

        dim_json["impeller0"]["blades"]["innerRadius"] = (double)impeller0.blades.innerRadius;
        dim_json["impeller0"]["blades"]["outerRadius"] = (double)impeller0.blades.outerRadius;
        dim_json["impeller0"]["blades"]["bottom"] = (double)impeller0.blades.bottom;
        dim_json["impeller0"]["blades"]["top"] = (double)impeller0.blades.top;
        dim_json["impeller0"]["blades"]["bladeThickness"] = (double)impeller0.blades.bladeThickness;

        dim_json["impeller0"]["disk"]["radius"] = (double)impeller0.disk.radius;
        dim_json["impeller0"]["disk"]["bottom"] = (double)impeller0.disk.bottom;
        dim_json["impeller0"]["disk"]["top"] = (double)impeller0.disk.top;

        dim_json["impeller0"]["hub"]["radius"] = (double)impeller0.hub.radius;
        dim_json["impeller0"]["hub"]["bottom"] = (double)impeller0.hub.bottom;
        dim_json["impeller0"]["hub"]["top"] = (double)impeller0.hub.top;



        std::ofstream out(filepath.c_str(), std::ofstream::out);
        out << dim_json;
        out.close();

        return 0;
    }
    catch(std::exception& e)
    {
        std::cerr << "Unhandled Exception reached parsing arguments: "
        << e.what() << ", application will now exit" << std::endl;
        return 1;
    }

    return 0;
}



