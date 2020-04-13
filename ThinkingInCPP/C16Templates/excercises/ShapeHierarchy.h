/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ShapeHierarchy.h
 * Author: default
 *
 * Created on December 21, 2019, 4:21 PM
 */

#ifndef SHAPEHIERARCHY_H
#define SHAPEHIERARCHY_H

class IObject {
public:
    
};

class IShapeEx {
public:
    
};

class OShapeEx : public IObject, IShapeEx {
public:
    
};

class CircleEx : public IShapeEx {
public:
    
};

class SquareEx : public IShapeEx {
public:
    
};

class TriangleEx : public IShapeEx {
public:
    
};

class OCircleEx : public CircleEx, public OShapeEx {
public:
    
};
class OSquareEx : public SquareEx, public OShapeEx {
public:
    
};
class OTriangleEx : public TriangleEx, public OShapeEx {
public:
    
};
#endif /* SHAPEHIERARCHY_H */

