#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

// using namespace std;
 const double epsilon = 0.000001;

std::list<Shape *> * shapeList ;
Rectangle  rec1(0,0,1,1);  // 1x1
Rectangle  rec2(0,0,2,2);  // 2x2
Rectangle  rec3(0,0,3,3);  // 3x3
Rectangle  rec4(0,0,4,4);  // 4x4

double * getPerimerter(std::list<Shape *> * shapeList) {
    double *fromShapeList = new double[4] ;
    fromShapeList[0] = (*shapeList->begin())->perimeter() ;
    shapeList->pop_front() ;
    fromShapeList[1] = (*shapeList->begin())->perimeter() ;
    shapeList->pop_front() ;
    fromShapeList[2] = (*shapeList->begin())->perimeter() ;
    shapeList->pop_front() ;
    fromShapeList[3] = (*shapeList->begin())->perimeter() ;
    return fromShapeList ;
}

double * getArea(std::list<Shape *> * shapeList) {
    double *fromShapeList = new double[4] ;
    fromShapeList[0] = (*shapeList->begin())->area() ;
    shapeList->pop_front() ;
    fromShapeList[1] = (*shapeList->begin())->area() ;
    shapeList->pop_front() ;
    fromShapeList[2] = (*shapeList->begin())->area() ;
    shapeList->pop_front() ;
    fromShapeList[3] = (*shapeList->begin())->area() ;
    return fromShapeList ;
}

double * getCompactness(std::list<Shape *> * shapeList) {
    double *fromShapeList = new double[4] ;
    fromShapeList[0] = (*shapeList->begin())->area() / (*shapeList->begin())->perimeter() ;
    shapeList->pop_front() ;
    fromShapeList[1] = (*shapeList->begin())->area() / (*shapeList->begin())->perimeter() ;
    shapeList->pop_front() ;
    fromShapeList[2] = (*shapeList->begin())->area() / (*shapeList->begin())->perimeter() ;
    shapeList->pop_front() ;
    fromShapeList[3] = (*shapeList->begin())->area() / (*shapeList->begin())->perimeter() ;
    return fromShapeList ;
}


TEST (Sort, sortByIncreasingPerimeter) {
    shapeList = new std::list<Shape *> ;
    shapeList->push_back(&rec1);
    shapeList->push_back(&rec4);
    shapeList->push_back(&rec3);
    shapeList->push_back(&rec2);
    Sort::sortByIncreasingPerimeter(shapeList);
    double *fromShapeList = new double[4];
    fromShapeList = getPerimerter(shapeList);
    
    double ans[4] = {4,8,12,16} ;
    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR( fromShapeList[i],ans[i],epsilon);
    }
    delete shapeList ;
}

TEST (Sort, sortByDecreasingPerimeter) {
    shapeList = new std::list<Shape *> ;
    shapeList->push_back(&rec3);
    shapeList->push_back(&rec4);
    shapeList->push_back(&rec1);
    shapeList->push_back(&rec2);
    Sort::sortByDecreasingPerimeter(shapeList);
    double *fromShapeList = new double[4];
    fromShapeList = getPerimerter(shapeList);
    
    double ans[4] = {16,12,8,4} ;
    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR( fromShapeList[i],ans[i],epsilon);
    }
    delete shapeList ;
}

TEST (Sort, sortByIncreasingArea) {
    shapeList = new std::list<Shape *> ;
    shapeList->push_back(&rec3);
    shapeList->push_back(&rec4);
    shapeList->push_back(&rec1);
    shapeList->push_back(&rec2);
    Sort::sortByIncreasingArea(shapeList);
    double *fromShapeList = new double[4];
    fromShapeList = getArea(shapeList);
    
    double ans[4] = {1,4,9,16} ;
    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR( fromShapeList[i],ans[i],epsilon);
    }
    delete shapeList ;
}

TEST (Sort, sortByDecreasingArea) {
    shapeList = new std::list<Shape *> ;
    shapeList->push_back(&rec3);
    shapeList->push_back(&rec2);
    shapeList->push_back(&rec4);
    shapeList->push_back(&rec1);
    Sort::sortByDecreasingArea(shapeList);
    double *fromShapeList = new double[4];
    fromShapeList = getArea(shapeList);
    
    double ans[4] = {16,9,4,1} ;
    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR( fromShapeList[i],ans[i],epsilon);
    }
    delete shapeList ;
}

TEST (Sort, sortByIncreasingCompactness) {
// Compactness = area/perimeter
    shapeList = new std::list<Shape *> ;
    shapeList->push_back(&rec3);
    shapeList->push_back(&rec2);
    shapeList->push_back(&rec4);
    shapeList->push_back(&rec1);
    Sort::sortByIncreasingCompactness(shapeList);
    double *fromShapeList = new double[4];
    fromShapeList = getCompactness(shapeList);
    
    double ans[4] = {0.25,0.5,0.75,1} ;
    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR( fromShapeList[i],ans[i],epsilon);
    }
    delete shapeList ;
}

#endif
