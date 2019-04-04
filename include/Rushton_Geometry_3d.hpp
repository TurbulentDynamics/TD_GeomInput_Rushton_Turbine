//
//  Header.h
//  TD_GeomInput_Rushton_Turbine
//
//  Created by Nile Ó Broin on 13/02/2019.
//  Copyright © 2019 Nile Ó Broin. All rights reserved.
//

#ifndef Rushton_Geometry_3d_hpp
#define Rushton_Geometry_3d_hpp

#include <vector>
#include <stdio.h>
#include <cstring>

#include "define_typealias.h"
#include "define_datastructures.hpp"

#include "Inline.hpp"
#include "timer.hpp"


#include "Rushton_Geometry_Config.hpp"

#include "Geom_Dims.hpp"
#include "Node_Dims.hpp"
#include "Grid_Dims.hpp"




struct GeomData
{
    tGeomShape resolution = 0.0f;
    tGeomShape r_polar = 0.0f;
    tGeomShape t_polar = 0.0f;
    
    tGeomShape i_cart_fp = 0.0f;
    tGeomShape j_cart_fp = 0.0f;
    tGeomShape k_cart_fp = 0.0f;

    //Used in forcing
    tGeomShape u_delta_fp = 0.0f;
    tGeomShape v_delta_fp = 0.0f;
    tGeomShape w_delta_fp = 0.0f;

    
    tGeomShape i_cart_fraction = 0.0f;
    tGeomShape j_cart_fraction = 0.0f;
    tGeomShape k_cart_fraction = 0.0f;


    tNi i_cart = 0;
    tNi j_cart = 0;
    tNi k_cart = 0;  //cell point

    
    bool is_solid = 0; //Either 0 surface, or 1 solid (the cells between the surface)


    // Remember constructor for data types that does not get fully initialised each time they are used.
    // When the system hands out new memory to a program, the memory is cleared (zeroed), but when a
    // program frees some memory and then ask for new (later) it can get the same memory back but
    // without it being zeroed out.
    GeomData()
    {
        memset(this, 0, sizeof(GeomData));
    }


};




struct Point3D
{
    tGeomShape x, y, z;
};




class Geometry {


private:
    GeometryConfig tankConfig;

    Grid_Dims grid;
    Node_Dims node;
    Node_Bounds node_bounds;

    tGeomShape calc_this_step_impeller_increment(tStep step);


    Point3D center;

    
    void inline UpdateCoordinateFraction(tGeomShape coordinate, tNi *integerPart, tGeomShape *fractionPart);
    void inline UpdatePointFractions(GeomData &point);
    std::vector<GeomData> CreateTankWall(tNi lowerLimitY, tNi upperLimitY, bool get_solid);
    std::vector<GeomData> CreateBaffles(tNi lowerLimitY, tNi upperLimitY, bool get_solid);


    std::vector<GeomData> CreateImpellerBlades(tStep step, tNi lowerLimitY, tNi upperLimitY, bool get_solid);
    std::vector<GeomData> CreateImpellerDisk(tNi lowerLimitY, tNi upperLimitY, bool get_solid);
    std::vector<GeomData> CreateImpellerHub(tNi lowerLimitY, tNi upperLimitY, bool get_solid);
    std::vector<GeomData> CreateImpellerShaft(tNi lowerLimitY, tNi upperLimitY, bool get_solid);

    void print_val(const std::vector<GeomData> &geom);

public:

    //Tank and baffle surface points
    std::vector<GeomData> geom_fixed_surface;

    //Baffles internal points
    std::vector<GeomData> geom_fixed_internal;

    //Blade surface and internal points
    std::vector<GeomData> geom_rotating_surface_and_internal_blades;

    //Shaft and hub internal points
//    std::vector<GeomData> geom_rotating_static_internal;


    void Init(Grid_Dims, Node_Dims, GeometryConfig);

    tGeomShape Init_at_angle(tGeomShape angle, tStep step, Grid_Dims grid, Node_Dims node, GeometryConfig tankConfig);

    

    tGeomShape Update(Multi_Timer &timer, tStep step, tGeomShape impellerTheta);
    void setRotatingSolid(Multi_Timer &timer, tStep step, tGeomShape set_impellerTheta);



    void print_geometry_csv(const std::string &filename, const std::vector<GeomData> &geom, const std::string append);

    void print_geometry_points_csv(const std::string &filename, const std::vector<GeomData> &geom, const std::string append = "");
    
    std::vector<GeomData> load_geom_data_from_csv(const std::string &srcFile);



    Geom_Dims get_geom_dims();

    
    void clear_vectors(){

        geom_fixed_surface.clear();
        geom_fixed_internal.clear();


        geom_rotating_surface_and_internal_blades.clear();
//        geom_rotating_static_internal.clear();
    }


    void Checkpoint_Load();
    void Checkpoint_Save();


};




#endif
