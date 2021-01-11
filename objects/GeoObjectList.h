#ifndef VRT_GEO_LIST_H
#define VRT_GEO_LIST_H

#include <vector>
#include <memory>
#include "GeoObject.h"

//want to use smart pointers
using std::make_shared;
using std::shared_ptr;

namespace vrt {

    //this is a wrapper of an std:::vector of GeoObject Pointer
    class GeoObjectList : public GeoObject {
    public:
        //methods
        void addObject(shared_ptr<GeoObject> ptr);
        void deleteObject();
        bool empty();
        bool empty() const;
        size_t listSize();
        void listClear();
        bool hit(const Ray& ray, double t_min, double t_max, HitRec& record) const override;

    private:
        //the vector of Base Class (GeoObject) pointers
        std::vector<shared_ptr<GeoObject>> list;
    };

    //class methods
    void GeoObjectList::addObject(shared_ptr<GeoObject> ptr) {
        list.emplace_back(ptr);
    }

    void GeoObjectList::deleteObject() {
        list.pop_back();
    }

    bool GeoObjectList::empty() {
        return list.empty();
    }

    bool GeoObjectList::empty() const {
        return list.empty();
    }

    size_t GeoObjectList::listSize() {
        return list.size();
    }

    void GeoObjectList::listClear(){
        list.clear();
    }

    bool GeoObjectList::hit(const Ray& ray, double t_min, double t_max, HitRec& record) const {
        
        HitRec temp;
        bool hitAnything = false;
        auto closest = t_max;

        for (const auto& object : list) {
            if (object->hit(ray, t_min, closest, temp)) {
                hitAnything = true;
                closest = temp.t_;
                record = temp;
            }
        }
        
        return hitAnything; //hit something
    }   
    
} //namespace vrt

#endif