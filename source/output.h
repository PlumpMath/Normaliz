/*
 * Normaliz
 * Copyright (C) 2007-2014  Winfried Bruns, Bogdan Ichim, Christof Soeger
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As an exception, when this program is distributed through (i) the App Store
 * by Apple Inc.; (ii) the Mac App Store by Apple Inc.; or (iii) Google Play
 * by Google Inc., then that store may impose any digital rights management,
 * device limits and/or redistribution restrictions that are required by its
 * terms of service.
 */

//---------------------------------------------------------------------------
#ifndef OUTPUT_H
#define OUTPUT_H
//---------------------------------------------------------------------------

#include "libnormaliz/cone.h"

using namespace std;
using namespace libnormaliz;

//---------------------------------------------------------------------------

template<typename Integer>
class Output {
    string name;
    bool out;
    bool inv;
    bool ext;
    bool esp;
    bool typ;
    bool egn;
    bool gen;
    bool cst;
    bool tri;
    bool tgn;
    bool ht1;
    bool dec;
    bool lat;
    bool mod;
    bool msp;
    Cone<Integer>* Result;
    size_t dim;
    bool homogeneous;
    string of_cone;
    string of_monoid;
    string of_polyhedron;
    
    bool lattice_ideal_input;


//---------------------------------------------------------------------------
public:
//---------------------------------------------------------------------------
//                        Construction and destruction
//---------------------------------------------------------------------------

    Output();  //main constructor
    // default copy constructor and destructors are ok
    // the Cone Object is handled at another place

//---------------------------------------------------------------------------
//                                Data acces
//---------------------------------------------------------------------------

    void read() const;                   // to be modified, just for tests

    void set_name(const string& n);
    void setCone(Cone<Integer> & C);
  
    void set_write_out(const bool& flag);             //sets the write .out flag
    void set_write_inv(const bool& flag);             //sets the write .inv flag
    void set_write_ext(const bool& flag);             //sets the write .ext flag
    void set_write_esp(const bool& flag);             //sets the write .esp flag
    void set_write_typ(const bool& flag);             //sets the write .typ flag
    void set_write_egn(const bool& flag);             //sets the write .egn flag
    void set_write_gen(const bool& flag);             //sets the write .gen flag
    void set_write_cst(const bool& flag);             //sets the write .cst flag
    void set_write_tri(const bool& flag);             //sets the write .tri flag
    void set_write_tgn(const bool& flag);             //sets the write .tgn flag
    void set_write_ht1(const bool& flag);             //sets the write .ht1 flag
    void set_write_dec(const bool& flag);             //sets the write .dec flag
    void set_write_lat(const bool& flag);             //sets the write .lat flag
    void set_write_mod(const bool& flag);             //sets the write .mod flag
    void set_write_msp(const bool& flag);             //sets the write .msp flag
    void set_write_extra_files();                     //sets some flags to true
    void set_write_all_files();                       //sets most flags to true
  
    void write_matrix_ext(const Matrix<Integer>& M) const; //writes M to file name.ext
    void write_matrix_lat(const Matrix<Integer>& M) const; //writes M to file name.lat
    void write_matrix_esp(const Matrix<Integer>& M) const; //writes M to file name.esp
    void write_matrix_typ(const Matrix<Integer>& M) const; //writes M to file name.typ
    void write_matrix_egn(const Matrix<Integer>& M) const; //writes M to file name.egn
    void write_matrix_gen(const Matrix<Integer>& M) const; //writes M to file name.gen
    void write_matrix_mod(const Matrix<Integer>& M) const; //writes M to file name.mod 
    void write_matrix_msp(const Matrix<Integer>& M) const; //writes M to file name.msp
    void write_tri() const; //writes the .tri file
    void write_Stanley_dec() const;
    void write_matrix_ht1(const Matrix<Integer>& M) const; //writes M to file name.ht1

    void write_inv_file() const;
    
    void set_lattice_ideal_input(bool lattice_odeal_input);


//---------------------------------------------------------------------------
//                         Output Algorithms
//---------------------------------------------------------------------------

    void write_files() const;
    void writeWeightedEhrhartSeries(ofstream& out) const;

};
//class end *****************************************************************

//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

