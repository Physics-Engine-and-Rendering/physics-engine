#pragma once

#include <iostream>
#include "body.hpp"
#include "contact_t.h"

bool Intersect(const Body *bodyA, const Body *bodyB, contact_t& contact);