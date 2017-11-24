#include <list>
#include "Shapes.h"

class Sort {
    
    bool compareByPerimeter(const Shape * first, const Shape * second ) {
        return ( first->perimeter() > second->perimeter() );
    }
    public :static void sortByIncreasingPerimeter(std::list<Shape *> * shapeList){
        
        shapeList->sort([] (const Shape * first, const Shape * second )
        {
            return first->perimeter() < second->perimeter() ;
            // 小的會換到前面
        });
        
//        std::list<Shape *> ::iterator iter = shapeList->begin();
//        std::list<Shape *> ::iterator listEnd= shapeList->end();
//        for ( ; iter != listEnd ; iter++ ) {
//            std::cout << (*iter)->perimeter() << "\n";
//        } // for print

    }

    public :static void sortByDecreasingPerimeter(std::list<Shape *> * shapeList){
        shapeList->sort([] (const Shape * first, const Shape * second )
        {
            return first->perimeter() > second->perimeter() ;
                            // 大的會換到前面
        });
    }

    public :static void sortByIncreasingArea(std::list<Shape *> * shapeList){
        shapeList->sort([] (const Shape * first, const Shape * second )
        {
            return first->area() < second->area() ;
                            // 小的會換到前面
        });
    }

    public :static void sortByDecreasingArea(std::list<Shape *> * shapeList){
        shapeList->sort([] (const Shape * first, const Shape * second )
        {
            return first->area() > second->area() ;
                            // 大的會換到前面
        });
    }
  
    public :static void sortByIncreasingCompactness(std::list<Shape *> * shapeList){
        // Compactness = area/perimeter
        shapeList->sort([] (const Shape * first, const Shape * second )
        {
            return (first->area() / first->perimeter() )< ( second->area()/ second->perimeter() )  ;
                            // 小的會換到前面
        });
    }
  
};
