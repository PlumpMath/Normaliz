/*
 * Normaliz 2.5
 * Copyright (C) 2007-2010  Winfried Bruns, Bogdan Ichim, Christof Soeger
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


#include "sublattice_representation.h"
#include "vector_operations.h"

//---------------------------------------------------------------------------

namespace libnormaliz {

/**
 * creates a representation of Z^n as a sublattice of itself
 */
template<typename Integer>
Sublattice_Representation<Integer>::Sublattice_Representation(int n) {
	dim = n;
	rank = n;
	index = 1;
	A = Matrix<Integer>(n);
	B = Matrix<Integer>(n);
	c = 1;
}

//---------------------------------------------------------------------------

/**
 * Main Constructor
 * creates a representation of a sublattice of Z^n
 * if direct_summand is false the sublattice is generated by the rows of M
 * otherwise it is a direct summand of Z^n containing the rows of M
 */
template<typename Integer>
Sublattice_Representation<Integer>::Sublattice_Representation(const Matrix<Integer>& M, bool direct_summand) {
	Lineare_Transformation<Integer> Basis_Change = Transformation(M);
	initialize(Basis_Change, direct_summand);
}

template<typename Integer>
Sublattice_Representation<Integer>::Sublattice_Representation(const Lineare_Transformation<Integer>& Basis_Change, bool direct_summand) {
	initialize(Basis_Change, direct_summand);
}

template<typename Integer>
void Sublattice_Representation<Integer>::initialize(const Lineare_Transformation<Integer>& Basis_Change, bool direct_summand) {
	int i,j;
	
	rank = Basis_Change.get_rank();
	if (rank==0) {
		errorOutput()<<"warning: matrix has rank 0. Please check input data."<<endl;
	}

	//here: M=LCR  in LT: LMR=C
	Matrix<Integer> R = Basis_Change.get_right_inv();
	Matrix<Integer> R_Inv = Basis_Change.get_right();

	dim = R.nr_of_columns();
//	cout << "dim = "<<dim<<"    rank = "<<rank<<endl;
	A = Matrix<Integer>(rank, dim);
	B = Matrix<Integer>(dim, rank);
	c = 1;
	index = 1;

	for (i = 1; i <= rank; i++) {
		for (j = 1; j <= dim; j++) {
			A.write(i,j, R.read(i,j));
			B.write(j,i, R_Inv.read(j,i));
		}
	}
	

	Matrix<Integer> D = Basis_Change.get_center();

//	cout <<"rank="<<rank<<" Dia: "<<D.nr_of_rows()<<"x"<<D.nr_of_columns()<<endl;

	if ( direct_summand ) {
		for (i = 1; i <= rank; i++) {
			index *= D.read(i,i);
		}
		index = Iabs(index);
		
	} else {
		Matrix<Integer> Diagonal(rank);
		for (i = 1; i <= rank; i++) {
			Diagonal.write(i,i,D.read(i,i));
		}
		A = Diagonal.multiplication(A);
		vector<Integer> c_vector = Diagonal.diagonale();
		
		c = v_lcm(c_vector);
		//invert Diagonal, multiply c to maintain integer coefficients
		for (i = 1; i <= rank; i++) {
			Diagonal.write(i,i,c/c_vector[i-1]);
		}
		B = B.multiplication(Diagonal);
	}	

}

//---------------------------------------------------------------------------

template<typename Integer>
Sublattice_Representation<Integer>::Sublattice_Representation(const Sublattice_Representation& SR) {
	A = SR.A;
	B = SR.B;
	c = SR.c;
	dim = SR.dim;
	rank = SR.rank;
	index = SR.index;
}
//---------------------------------------------------------------------------

template<typename Integer>
Sublattice_Representation<Integer>::~Sublattice_Representation() {}


//---------------------------------------------------------------------------
//                       Manipulation operations
//---------------------------------------------------------------------------

/* first this then SR when going from Z^n to Z^r */
template<typename Integer>
void Sublattice_Representation<Integer>::compose(const Sublattice_Representation& SR) {
	assert(rank == SR.dim); //TODO vielleicht doch exception?

	rank = SR.rank;
	index = index * SR.index;
	// A = SR.A * A
	A = SR.A.multiplication(A);
	// B = B * SR.B
	B = B.multiplication(SR.B);
	c = c * SR.c;
	
	//check if a factor can be extraced from B  //TODO necessary?
	Integer g = B.matrix_gcd();
	g = gcd(g,c);  //TODO necessary??
	if (g > 1) {
		c /= g;
		B.scalar_division(g);
	}
}

//---------------------------------------------------------------------------
//                       Transformations
//---------------------------------------------------------------------------

template<typename Integer>
Matrix<Integer> Sublattice_Representation<Integer>::to_sublattice (const Matrix<Integer>& M) const {
	Matrix<Integer> N = M.multiplication(B);
	if (c!=1) N.scalar_division(c);
	return N;
}

template<typename Integer>
Matrix<Integer> Sublattice_Representation<Integer>::from_sublattice (const Matrix<Integer>& M) const {
	Matrix<Integer> N = M.multiplication(A);
	return N;
}

template<typename Integer>
Matrix<Integer> Sublattice_Representation<Integer>::to_sublattice_dual (const Matrix<Integer>& M) const {
	Matrix<Integer> N = M.multiplication(A.transpose());
	N.make_prime();
	return N;
}

template<typename Integer>
Matrix<Integer> Sublattice_Representation<Integer>::from_sublattice_dual (const Matrix<Integer>& M) const {
	Matrix<Integer> N = M.multiplication(B.transpose());
	N.make_prime();
	return N;
}


template<typename Integer>
vector<Integer> Sublattice_Representation<Integer>::to_sublattice (const vector<Integer>& V) const {
	vector<Integer> N = B.VxM(V);
	if (c!=1) v_scalar_division(N,c);
	return N;
}

template<typename Integer>
vector<Integer> Sublattice_Representation<Integer>::from_sublattice (const vector<Integer>& V) const {
	vector<Integer> N = A.VxM(V);
	return N;
}

template<typename Integer>
vector<Integer> Sublattice_Representation<Integer>::to_sublattice_dual (const vector<Integer>& V) const {
	vector<Integer> N = (A.transpose()).VxM(V);
	return v_make_prime(N);
}

template<typename Integer>
vector<Integer> Sublattice_Representation<Integer>::from_sublattice_dual (const vector<Integer>& V) const {
	vector<Integer> N = (B.transpose()).VxM(V);
	return v_make_prime(N);
}

//---------------------------------------------------------------------------
//						 Data access
//---------------------------------------------------------------------------

/* returns the dimension of the ambient space */
template<typename Integer>
int Sublattice_Representation<Integer>::get_dim() const {
	return dim;
}

//---------------------------------------------------------------------------

/* returns the rank of the sublattice */
template<typename Integer>
int Sublattice_Representation<Integer>::get_rank() const {
	return rank;
}

//---------------------------------------------------------------------------

/* returns the index of the sublattice */
template<typename Integer>
Integer Sublattice_Representation<Integer>::get_index() const {
	return index;
}

//---------------------------------------------------------------------------

template<typename Integer>
Matrix<Integer> Sublattice_Representation<Integer>::get_A() const {
	return A;
} 

//---------------------------------------------------------------------------

template<typename Integer>
Matrix<Integer> Sublattice_Representation<Integer>::get_B() const {
	return B;
}

//---------------------------------------------------------------------------

template<typename Integer>
Integer Sublattice_Representation<Integer>::get_c() const {
	return c;
}

//---------------------------------------------------------------------------

/* returns the congruences defining the sublattice */
template<typename Integer>
Matrix<Integer> Sublattice_Representation<Integer>::get_congruences() const {
	if ( c == 1 ) { // no congruences then
		return Matrix<Integer>(0,dim+1);
	}

	// Cong is B transposed and with an extra column for the modul m
	Matrix<Integer> Cong = B;
	Cong.append(Matrix<Integer>(1,rank));
	Cong = Cong.transpose();
	vector<Integer> gcds = Cong.make_prime();
	Integer m; //the modul
	Integer rowgcd;
	Matrix<Integer> Cong2(0,dim+1); //only the relavant congruences
	vector<Integer> new_row;
	for (int j=1; j<=rank; j++) {
		m = c/gcds[j-1];
		if ( m != 1 ) {
			new_row = Cong.read(j);
			v_reduction_modulo(new_row,m);  
			//new_row cannot be divisible by a factor of m
			//so make_prime divides by an invertible element
			new_row = v_make_prime(new_row,rowgcd);  
			assert(gcd(m,rowgcd) == 1);
			new_row[dim] = m;
			Cong2.append(new_row);
		}
	}
	return Cong2;
}

}
