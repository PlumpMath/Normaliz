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

/**
 * The class Sublattice_Representation represents a sublattice of Z^n as Z^r.
 * To transform vectors of the sublattice  use:
 *    Z^r --> Z^n    and    Z^n -->  Z^r
 *     v  |-> vA             u  |-> (uB)/c
 * A  r x n matrix
 * B  n x r matrix
 * c  Integer
 */

#ifndef SUBLATTICE_REPRESENTATION_H
#define SUBLATTICE_REPRESENTATION_H

#include <vector>
#include "libnormaliz.h"
#include "matrix.h"

//---------------------------------------------------------------------------

namespace libnormaliz {

template<typename Integer> class Matrix;
// template<typename Integer> class Lineare_Transformation;
using std::vector;


template<typename Integer>
class Sublattice_Representation {

    template<typename> friend class Sublattice_Representation;
    
	size_t dim, rank;
	Matrix<Integer> A;
	Matrix<Integer> B;
	Integer c;
	mpz_class index;
    mutable mpz_class external_index;
    mutable Matrix<Integer> Equations;
    mutable bool Equations_computed;
    mutable Matrix<Integer> Congruences;
    mutable bool Congruences_computed;
    
    void make_equations() const;
    void make_congruences() const;

//---------------------------------------------------------------------------
public:
//---------------------------------------------------------------------------
//						Construction and destruction
//---------------------------------------------------------------------------

	/**
	 * creates a dummy object
	 */
	Sublattice_Representation() {}

	/**
	 * creates a representation of Z^n as a sublattice of itself
	 */
	Sublattice_Representation(size_t n);
	
	/**
	 * Main Constructor
	 * creates a representation of a sublattice of Z^n
	 * if direct_summand is false the sublattice is generated by the rows of M
	 * otherwise it is a direct summand of Z^n containing the rows of M
	 */
	Sublattice_Representation(const Matrix<Integer>& M, bool take_saturation);
	// Sublattice_Representation(const Lineare_Transformation<Integer>& LT, bool take_saturation);

//---------------------------------------------------------------------------
//                       Manipulation operations
//---------------------------------------------------------------------------	

	/* like the matching constructor */
	void initialize(const Matrix<Integer>& M, bool take_saturation, bool& success);

	/* first this then SR when going from Z^n to Z^r */
	void compose(const Sublattice_Representation<Integer>& SR);

//---------------------------------------------------------------------------
//                       Transformations
//---------------------------------------------------------------------------

	Matrix<Integer> to_sublattice (const Matrix<Integer>& M) const;
	Matrix<Integer> from_sublattice (const Matrix<Integer>& M) const;
	Matrix<Integer> to_sublattice_dual (const Matrix<Integer>& M) const;
	Matrix<Integer> from_sublattice_dual (const Matrix<Integer>& M) const;

	vector<Integer> to_sublattice (const vector<Integer>& V) const;
	vector<Integer> from_sublattice (const vector<Integer>& V) const;
	vector<Integer> to_sublattice_dual (const vector<Integer>& M) const;
	vector<Integer> from_sublattice_dual (const vector<Integer>& V) const;

	vector<Integer> to_sublattice_dual_no_div (const vector<Integer>& M) const;
//---------------------------------------------------------------------------
//						 Data acces
//---------------------------------------------------------------------------

	/* returns the dimension of the ambient space */
	size_t get_dim() const;

	/* returns the rank of the sublattice */
	size_t get_rank() const;

	/* returns the index of the sublattice */
	mpz_class get_index() const;

	Matrix<Integer> get_A() const;
	
	Matrix<Integer> get_B() const;
	
	Integer get_c() const;

    Matrix<Integer> get_equations() const;	
    Matrix<Integer> get_congruences() const;
    mpz_class get_external_index() const;

};

}

//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
