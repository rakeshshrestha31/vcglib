/****************************************************************************
* VCGLib                                                            o o     *
* Visual and Computer Graphics Library                            o     o   *
*                                                                _   O  _   *
* Copyright(C) 2004                                                \/)\/    *
* Visual Computing Lab                                            /\/|      *
* ISTI - Italian National Research Council                           |      *
*                                                                    \      *
* All rights reserved.                                                      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *   
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/
/****************************************************************************
  History

$Log: not supported by cvs2svn $
Revision 1.27  2008/04/03 23:12:28  cignoni
compacted two pair of empty components to shorten derivation chains

Revision 1.26  2008/03/17 11:39:14  ganovelli
added curvature and curvatruredir (compiled .net 2005 and gcc)

Revision 1.25  2008/02/05 10:11:34  cignoni
A small typo (a T:: instead of TT::)

Revision 1.24  2008/02/04 21:26:49  ganovelli
added ImportLocal which imports all local attributes into vertexplus and faceplus.
A local attribute is everything (N(), C(), Q()....) except pointers to other simplices
(i.e. FFAdj, VFAdj, VertexRef) which are set to NULL.
Added some function for const attributes

Revision 1.23  2007/06/04 15:40:22  turini
Add vertex-tetrahedron adjacency component VTAdj.

Revision 1.22  2007/03/12 15:37:21  tarini
Texture coord name change!  "TCoord" and "Texture" are BAD. "TexCoord" is GOOD.

Revision 1.21  2007/02/18 07:41:32  cignoni
Corrected small syntax errors detected by gcc

Revision 1.20  2007/02/12 19:00:56  ganovelli
added Name(std:vector<std::string>& n) that fills n with the names of the attribute of the vertex type

Revision 1.19  2006/12/11 23:40:57  ganovelli
Has*Opt migrated to Has*Occ

Revision 1.18  2006/11/28 22:34:28  cignoni
Added default constructor with null initialization to adjacency members.
AddFaces and AddVertices NEED to know if the topology is correctly computed to update it.

Revision 1.17  2006/01/09 13:58:56  cignoni
Added Initialization of Color in Vertex and Face Components

Revision 1.16  2005/11/22 23:58:03  cignoni
Added intiailization of flags to zero in the constructor,

Revision 1.15  2005/11/18 15:44:51  cignoni
Access to constant normal changed from by val to by reference

Revision 1.14  2005/11/16 23:02:37  cignoni
Added some missing members to EmptyMark
Standardized name of flags. It is plural becouse each simplex has many flag.

Revision 1.13  2005/11/14 23:50:57  cignoni
Added Incremental Mark

Revision 1.12  2005/11/12 18:35:49  cignoni
Changed HasFlag -> HasFlags

Revision 1.11  2005/11/01 18:17:52  cignoni
Added an assert(0) in all the accesses to empty components

Revision 1.10  2005/10/15 16:24:10  ganovelli
Working release (compilata solo su MSVC), component_occ � migrato da component_opt

Revision 1.9  2005/10/14 13:30:07  cignoni
Added constant access functions and reflective functions (HasSomething stuff)
to all the components This is the first really working version...

Revision 1.8  2005/10/07 15:19:54  cignoni
minor updates to keep it in line with the rest of the library

Revision 1.7  2004/05/10 13:50:32  cignoni
Updated names of adj functions to the new standards

Revision 1.6  2004/04/05 11:53:06  cignoni
addend constant access funcs

Revision 1.5  2004/04/03 13:35:51  cignoni
minor changes

Revision 1.4  2004/03/31 13:15:28  cignoni
Added optional cpmponent

Revision 1.3  2004/03/31 12:28:37  ganovelli
*** empty log message ***

Revision 1.2  2004/03/29 14:26:38  cignoni
Error in color

Revision 1.1  2004/03/29 08:36:26  cignoni
First working version!


****************************************************************************/
#ifndef __VCG_VERTEX_PLUS_COMPONENT
#define __VCG_VERTEX_PLUS_COMPONENT
#include <vector>
#include <string>
#include <vcg/space/point3.h>
#include <vcg/space/texcoord2.h>
#include <vcg/space/color4.h>

namespace vcg {
  namespace vert {
/*
Some naming Rules
All the Components that can be added to a vertex should be defined in the namespace vert:

*/

/*------------------------- EMPTY COORD & NORMAL -----------------------------------------*/ 
template <class T> class EmptyCoordNormal: public T {
public:
  typedef vcg::Point3f CoordType;
  typedef CoordType::ScalarType      ScalarType;

  CoordType &P() { static CoordType coord(0, 0, 0); return coord; }
  const CoordType &P() const { static CoordType coord(0, 0, 0);  assert(0); return coord; }
  const CoordType &cP() const { static CoordType coord(0, 0, 0);  assert(0); return coord; }
  CoordType &UberP() { static CoordType coord(0, 0, 0); return coord; }
	static bool HasCoord()   { return false; }

  typedef vcg::Point3s NormalType;
  NormalType &N() { static NormalType dummy_normal(0, 0, 0);  assert(0); return dummy_normal; }
  const NormalType cN()const { static NormalType dummy_normal(0, 0, 0);  assert(0); return dummy_normal; }
 	static bool HasNormal()   { return false; }
  static bool HasNormalOcc()   { return false; }
	template < class LeftV>
	void ImportLocal(const LeftV  & left ) { T::ImportLocal( left); } 
  static void Name(std::vector<std::string> & name){T::Name(name);}
};

/*-------------------------- COORD ----------------------------------------*/ 

template <class A, class T> class Coord: public T {
public:
  typedef A CoordType;
  typedef typename CoordType::ScalarType      ScalarType;
  CoordType &P() { return _coord; }
  const CoordType &P() const { return _coord; }
  const CoordType &cP() const { return _coord; }
  CoordType &UberP() { return _coord; }

	template < class LeftV>
	void ImportLocal(const LeftV  & left ) { P().Import(left.cP()); T::ImportLocal( left); } 
  static bool HasCoord()   { return true; }
	static void Name(std::vector<std::string> & name){name.push_back(std::string("Coord"));T::Name(name);}

private:
  CoordType _coord;    
};
template <class T> class Coord3f: public Coord<vcg::Point3f, T> {
public:	static void Name(std::vector<std::string> & name){name.push_back(std::string("Coord3f"));T::Name(name);}
};
template <class T> class Coord3d: public Coord<vcg::Point3d, T> {
public: static void Name(std::vector<std::string> & name){name.push_back(std::string("Coord3d"));T::Name(name);}
};

/*-------------------------- NORMAL ----------------------------------------*/ 

template <class A, class T> class Normal: public T {
public:
  typedef A NormalType;
  NormalType &N() { return _norm; }
  const NormalType &cN() const { return _norm; }
	template < class LeftV>
	void ImportLocal(const LeftV  & left ) { N() = left.cN(); T::ImportLocal( left); }
  static bool HasNormal()   { return true; }
	static void Name(std::vector<std::string> & name){name.push_back(std::string("Normal"));T::Name(name);}

private:
  NormalType _norm;    
};

template <class T> class Normal3s: public Normal<vcg::Point3s, T> {
public:static void Name(std::vector<std::string> & name){name.push_back(std::string("Normal3s"));T::Name(name);}
};
template <class T> class Normal3f: public Normal<vcg::Point3f, T> {
public:	static void Name(std::vector<std::string> & name){name.push_back(std::string("Normal3f"));T::Name(name);}
};
template <class T> class Normal3d: public Normal<vcg::Point3d, T> {
public:	static void Name(std::vector<std::string> & name){name.push_back(std::string("Normal3d"));T::Name(name);}
};


/*-------------------------- INCREMENTAL MARK  ----------------------------------------*/ 

template <class T> class EmptyMark: public T {
public:
  static bool HasMark()   { return false; }
  static bool HasMarkOcc()   { return false; }
  inline void InitIMark()    {  }
  inline int & IMark()       { assert(0); static int tmp=-1; return tmp;}
  inline const int & IMark() const {return 0;}
	template < class LeftV>
	void ImportLocal(const LeftV  & left ) { T::ImportLocal( left); }
	static void Name(std::vector<std::string> & name){T::Name(name);}

};
template <class T> class Mark: public T {
public:
  static bool HasMark()      { return true; }
  static bool HasMarkOcc()   { return true; }
  inline void InitIMark()    { _imark = 0; }
  inline int & IMark()       { return _imark;}
  inline const int & IMark() const {return _imark;}
	template < class LeftV>
	void ImportLocal(const LeftV  & left ) { IMark() = left.IMark(); T::ImportLocal( left); }
	static void Name(std::vector<std::string> & name){name.push_back(std::string("Mark"));T::Name(name);}
    
 private:
	int _imark;
};

/*-------------------------- TEXCOORD ----------------------------------------*/ 

template <class TT> class EmptyTexCoord: public TT {
public:
  typedef vcg::TexCoord2<float,1> TexCoordType;
  TexCoordType &T() { static TexCoordType dummy_texcoord;  assert(0); return dummy_texcoord; }
	template < class LeftV>
	void ImportLocal(const LeftV  & left ) { TT::ImportLocal( left); }
  static bool HasTexCoord()   { return false; }
	static void Name(std::vector<std::string> & name){TT::Name(name);}

 };
template <class A, class TT> class TexCoord: public TT {
public:
  typedef A TexCoordType;
  TexCoordType &T() { return _t; }
  const TexCoordType &cT()  const { return _t; }
	template < class LeftV>
	void ImportLocal(const LeftV  & left ) { T() = left.cT(); TT::ImportLocal( left); }
  static bool HasTexCoord()   { return true; }
	static void Name(std::vector<std::string> & name){name.push_back(std::string("TexCoord"));TT::Name(name);}

private:
  TexCoordType _t;    
};

template <class TT> class TexCoord2s: public TexCoord<TexCoord2<short,1>, TT> {
	static void Name(std::vector<std::string> & name){name.push_back(std::string("TexCoord2s"));TT::Name(name);}

};
template <class TT> class TexCoord2f: public TexCoord<TexCoord2<float,1>, TT> {
	static void Name(std::vector<std::string> & name){name.push_back(std::string("TexCoord2f"));TT::Name(name);}
};
template <class TT> class TexCoord2d: public TexCoord<TexCoord2<double,1>, TT> {
	static void Name(std::vector<std::string> & name){name.push_back(std::string("TexCoord2d"));TT::Name(name);}
};

/*------------------------- FLAGS -----------------------------------------*/ 
template <class T> class EmptyBitFlags: public T {
public:
	typedef int FlagType;
  /// Return the vector of Flags(), senza effettuare controlli sui bit
  int &Flags() { static int dummyflags(0);  assert(0); return dummyflags; }
  const int Flags() const { return 0; }
	template < class LeftV>
	void ImportLocal(const LeftV  & left ) { T::ImportLocal( left); }
  static bool HasFlags()   { return false; }
	static void Name(std::vector<std::string> & name){T::Name(name);}

};

template <class T> class BitFlags:  public T {
public:
	BitFlags(){_flags=0;}
  typedef int FlagType;
  int &Flags() {return _flags; }
  const int Flags() const {return _flags; }
	template < class LeftV>
	void ImportLocal(const LeftV  & left ) { Flags() = left.Flags(); T::ImportLocal( left); }
  static bool HasFlags()   { return true; }
	static void Name(std::vector<std::string> & name){name.push_back(std::string("BitFlags"));T::Name(name);}

private:
  int  _flags;    
};

/*-------------------------- EMPTY COLOR & QUALITY ----------------------------------*/ 

template <class T> class EmptyColorQuality: public T {
public:
  typedef float QualityType;
  QualityType &Q() { static QualityType dummyQuality(0);  assert(0); return dummyQuality; }
	static bool HasQuality()   { return false; }

  typedef vcg::Color4b ColorType;
  ColorType &C() { static ColorType dumcolor(vcg::Color4b::White); assert(0); return dumcolor; }
	template < class LeftV>
	void ImportLocal(const LeftV  & left ) { T::ImportLocal( left); }
  static bool HasColor()   { return false; }
	static void Name(std::vector<std::string> & name){T::Name(name);}
};

/*-------------------------- Color  ----------------------------------*/ 

template <class A, class T> class Color: public T {
public:
  Color():_color(vcg::Color4b::White) {}
  typedef A ColorType;
  ColorType &C() { return _color; }
  const ColorType &C() const { return _color; }
  const ColorType &cC() const { return _color; }
	template < class LeftV>
	void ImportLocal(const LeftV  & left ) { C() = left.cC(); T::ImportLocal( left); }
  static bool HasColor()   { return true; }
	static void Name(std::vector<std::string> & name){name.push_back(std::string("Color"));T::Name(name);}

private:
  ColorType _color;    
};

template <class TT> class Color4b: public vert::Color<vcg::Color4b, TT> {
	public: static void Name(std::vector<std::string> & name){name.push_back(std::string("Color4b"));TT::Name(name);}
};

/*-------------------------- Quality  ----------------------------------*/ 

template <class A, class TT> class Quality: public TT {
public:
  typedef A QualityType;
  QualityType &Q() { return _quality; }
  const QualityType & cQ() const {return _quality; }
	template < class LeftV>
	void ImportLocal(const LeftV  & left ) { Q() = left.cQ(); TT::ImportLocal( left); }
  static bool HasQuality()   { return true; }
	static void Name(std::vector<std::string> & name){name.push_back(std::string("Quality"));TT::Name(name);}

private:
  QualityType _quality;    
};

template <class TT> class Qualitys: public Quality<short, TT> {
public: static void Name(std::vector<std::string> & name){name.push_back(std::string("Qualitys"));TT::Name(name);}
};
template <class TT> class Qualityf: public Quality<float, TT> {
public: static void Name(std::vector<std::string> & name){name.push_back(std::string("Qualityf"));TT::Name(name);}
};
template <class TT> class Qualityd: public Quality<double, TT> {
public: static void Name(std::vector<std::string> & name){name.push_back(std::string("Qualityd"));TT::Name(name);}
};

/*-------------------------- Curvature ----------------------------------*/ 

template <class TT> class EmptyCurvature: public TT {
public:
	typedef vcg::Point2<float> CurvatureType;

	float &Kh() {static float dummy = 0.f; return dummy;;}
	float &Kg() { static float dummy = 0.f; return dummy;}
	const float &cKh() const {static float dummy = 0.f; return dummy;;}
	const float &cKg()const  { static float dummy = 0.f; return dummy;}

  static bool HasCurvatureOcc()   { return false; }
  static bool HasCurvatureOcf()   { return false; }
  static bool HasCurvature()   { return false; }
	static void Name(std::vector<std::string> & name){TT::Name(name);}
};

template <class A, class TT> class Curvature: public TT {
public:
  typedef Point2<A> CurvatureType;
	typedef typename CurvatureType::ScalarType ScalarType;
	ScalarType  &Kh(){ return _hk[0];}
	ScalarType  &Kg(){ return _hk[1];}
	const ScalarType &cKh() const { return  _hk[0];}
	const ScalarType &cKg() const { return  _hk[1];}

  static bool HasCurvature()   { return true; }
	static void Name(std::vector<std::string> & name){name.push_back(std::string("Curvature"));TT::Name(name);}

private:
	Point2<A> _hk;    
};


template <class T> class Curvaturef: public Curvature< float, T> {
public:	static void Name(std::vector<std::string> & name){name.push_back(std::string("Curvaturef"));T::Name(name);}
};
template <class T> class Curvatured: public Curvature<double , T> {
public:	static void Name(std::vector<std::string> & name){name.push_back(std::string("Curvatured"));T::Name(name);}
};

/*-------------------------- Curvature Direction ----------------------------------*/ 

template <class S>
struct CurvatureDirBaseType{
	typedef Point3<S> VecType;
	typedef  S   ScalarType;
	CurvatureDirBaseType () {}
	Point3<S>max_dir,min_dir; // max and min curvature direction 
	S k1,k2;// max and min curvature values
};

template <class TT> class EmptyCurvatureDir: public TT {
public:
  typedef CurvatureDirBaseType<float> CurvatureDirType;

	Point3f &PD1(){static Point3f dummy(0,0,0); return dummy;}
	Point3f &PD2(){static Point3f dummy(0,0,0); return dummy;}
	const Point3f &cPD1() const {static Point3f dummy(0,0,0); return dummy;}
	const Point3f &cPD2()const {static Point3f dummy(0,0,0); return dummy;}

	float &K1(){ static float dummy(0);assert(0);return dummy;}
	float &K2(){ static float dummy(0);assert(0);return dummy;}
	const float &cK1()const { static float dummy(0);assert(0);return dummy;}
	const float &cK2()const { static float dummy(0);assert(0);return dummy;}

  static bool HasCurvatureDir()   { return false; }
	static void Name(std::vector<std::string> & name){TT::Name(name);}
};

template <class A, class TT> class CurvatureDir: public TT {
public:
  typedef A CurvatureDirType;
	typedef typename CurvatureDirType::VecType VecType;
	typedef typename CurvatureDirType::ScalarType ScalarType;

	VecType &PD1(){ return _curv.max_dir;}
	VecType &PD2(){ return _curv.min_dir;}
	const VecType &cPD1() const {return _curv.max_dir;}
	const VecType &cPD2() const {return _curv.min_dir;}

	ScalarType &K1(){ return _curv.k1;}
	ScalarType &K2(){ return _curv.k2;}
	const ScalarType &cK1() const {return _curv.k1;}
	const ScalarType &cK2()const  {return _curv.k2;}

  static bool HasCurvatureDir()   { return true; }
	static void Name(std::vector<std::string> & name){name.push_back(std::string("CurvatureDir"));TT::Name(name);}

private:
  CurvatureDirType _curv;    
};


template <class T> class CurvatureDirf: public CurvatureDir<CurvatureDirBaseType<float>, T> {
public:	static void Name(std::vector<std::string> & name){name.push_back(std::string("CurvatureDirf"));T::Name(name);}
};
template <class T> class CurvatureDird: public CurvatureDir<CurvatureDirBaseType<double>, T> {
public:	static void Name(std::vector<std::string> & name){name.push_back(std::string("CurvatureDird"));T::Name(name);}
};

/*----------------------------- VFADJ ------------------------------*/ 


template <class T> class EmptyVFAdj: public T {
public:
  typename T::FacePointer &VFp() { static typename T::FacePointer fp=0;  assert(0); return fp; }
  typename T::FacePointer cVFp() { static typename T::FacePointer fp=0;  assert(0); return fp; }
  int &VFi(){static int z=0; return z;};
	template < class LeftV>
	void ImportLocal(const LeftV  & left ) { T::ImportLocal( left); }
  static bool HasVFAdjacency()   {   return false; }
  static bool HasVFAdjacencyOcc()   {   return false; }
	static void Name(std::vector<std::string> & name){ T::Name(name);}
};

template <class T> class VFAdj: public T {
public:
  VFAdj(){_fp=0;}
  typename T::FacePointer &VFp() {return _fp; }
  typename T::FacePointer cVFp() {return _fp; }
  int &VFi() {return _zp; }
	template < class LeftV>
	void ImportLocal(const LeftV  & left ) { VFp() = NULL; T::ImportLocal( left); }
  static bool HasVFAdjacency()   {   return true; }
  static bool HasVFAdjacencyOcc()   {   return true; }
	static void Name(std::vector<std::string> & name){name.push_back(std::string("VFAdj"));T::Name(name);}

private:
  typename T::FacePointer _fp ;    
  int _zp ;    
};

/*----------------------------- VTADJ ------------------------------*/ 


template <class T> class EmptyVTAdj: public T {
public:
	typename T::TetraPointer &VTp() { static typename T::TetraPointer tp = 0;  assert(0); return tp; }
	typename T::TetraPointer cVTp() { static typename T::TetraPointer tp = 0;  assert(0); return tp; }
	int &VTi() { static int z = 0; return z; };
	static bool HasVTAdjacency() { return false; }
	static bool HasVTAdjacencyOcc() { return false; }
	static void Name( std::vector< std::string > & name ) { T::Name(name); }
};

template <class T> class VTAdj: public T {
public:
	VTAdj() { _tp = 0; }
	typename T::TetraPointer &VTp() { return _tp; }
	typename T::TetraPointer cVTp() { return _tp; }
	int &VTi() {return _zp; }
	static bool HasVTAdjacency() { return true; }
	static bool HasVTAdjacencyOcc()   {   return true; }
	static void Name( std::vector< std::string > & name ) { name.push_back( std::string("VTAdj") ); T::Name(name); }

private:
	typename T::TetraPointer _tp ;    
	int _zp ;    
};

  } // end namespace vert
}// end namespace vcg
#endif
