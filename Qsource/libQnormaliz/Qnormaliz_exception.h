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

#ifndef NORMALIZ_EXEPTION_H_
#define NORMALIZ_EXEPTION_H_

#include <exception>
#include <string>
#include <sstream>
#include <libQnormaliz/libQnormaliz.h>
#include <libQnormaliz/Qcone_property.h>

namespace libQnormaliz {

class NormalizException: public std::exception {
    public:
	virtual const char* what() const throw() = 0;
};

class ArithmeticException: public NormalizException {
    public:
    ArithmeticException() : msg("Arithmetic Overflow detected, try a bigger integer type!") {}
    ~ArithmeticException() throw() {}

    template<typename Number>
    ArithmeticException(const Number& convert_number){
        std::stringstream stream;
        stream << "Could not convert " << convert_number << ".\n";
        stream << "Arithmetic Overflow detected, try a bigger integer type!";
        msg = stream.str();
    }

	virtual const char* what() const throw() {
		return msg.c_str();
	}

    private:
    std::string msg;
};

class NonpointedException: public NormalizException {
    public:
	virtual const char* what() const throw() {
		return "Cone is not pointed.";
	}
};

class NotIntegrallyClosedException: public NormalizException {
    public:
	virtual const char* what() const throw() {
		return "Original monoid is not integrally closed.";
	}
};

class BadInputException: public NormalizException {
    public:
    BadInputException(const std::string& message) :
            msg("Some error in the normaliz input data detected: " + message)
    {}
    ~BadInputException() throw() {}

	virtual const char* what() const throw() {
		return msg.c_str();
	}

    private:
    std::string msg;
};

class NotComputableException: public NormalizException {
    public:
    NotComputableException(const std::string& message) : msg("Could not compute: " + message) {}
    NotComputableException(const ConeProperties& missing) {
        std::stringstream stream;
        stream << "Could not compute: " << missing << "!";
        msg = stream.str();
    }
    ~NotComputableException() throw() {}

    virtual const char* what() const throw() {
		return msg.c_str();
	}

    private:
    std::string msg;
};

class FatalException: public NormalizException {
    public:
    FatalException(const std::string& message) :
            msg("Fatal error: " + message +"\nThis should not happen, please contact the developers!")
    {}
    ~FatalException() throw() {}

	virtual const char* what() const throw() {
		return msg.c_str();
	}

    private:
    std::string msg;
};


} /* end namespace */

#endif /* LIBNORMALIZ_H_ */
