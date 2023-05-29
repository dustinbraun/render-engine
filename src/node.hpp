#pragma once

#include <iostream>

class Scene;

class Node {
public:
    virtual void enqueue(Scene& scene) {

    }

    virtual void enqueue_depth(Scene& scene) {

    }

    virtual void update(float dt) {
        
    }
};