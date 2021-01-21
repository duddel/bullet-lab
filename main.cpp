/*
Copyright (c) 2021 Alexander Scholz

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
#include "btBulletDynamicsCommon.h"
#include <cstdio>

int main()
{
    auto collisionCfg = new btDefaultCollisionConfiguration();
    auto collisionDispatcher = new btCollisionDispatcher(collisionCfg);
    auto broadphase = new btDbvtBroadphase();
    auto constraintSolver = new btSequentialImpulseConstraintSolver();

    auto dynamicsWorld = new btDiscreteDynamicsWorld(collisionDispatcher, broadphase, constraintSolver, collisionCfg);
    dynamicsWorld->setGravity(btVector3(0, -9.81, 0));

    // ground body
    auto groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0, -51, 0));
    btScalar groundMass(0.0);
    btVector3 groundLocalInertia(0, 0, 0);
    btRigidBody::btRigidBodyConstructionInfo groundRbInfo(groundMass, new btDefaultMotionState(groundTransform), groundShape, groundLocalInertia);
    groundRbInfo.m_restitution = 0.9f;
    auto groundBody = new btRigidBody(groundRbInfo);
    dynamicsWorld->addRigidBody(groundBody);

    // dynamic body
    auto ballShape = new btSphereShape(btScalar(1.0001));
    btTransform ballTransform;
    ballTransform.setIdentity();
    btScalar ballMass(1.0);
    btVector3 ballLocalInertia(0, 0, 0);
    ballShape->calculateLocalInertia(ballMass, ballLocalInertia);
    ballTransform.setOrigin(btVector3(2, 10, 0));
    btRigidBody::btRigidBodyConstructionInfo ballRbInfo(ballMass, new btDefaultMotionState(ballTransform), ballShape, ballLocalInertia);
    ballRbInfo.m_restitution = 0.9f;
    auto ballBody = new btRigidBody(ballRbInfo);
    dynamicsWorld->addRigidBody(ballBody);

    // simulate some world steps and visualize the height of the falling dynamic body
    for (int i = 0; i < 150; i++)
    {
        // 1/10 seconds is a coarse time delta. used here only to shorten the output
        dynamicsWorld->stepSimulation(1.f / 10.f, 10);

        btTransform trans;
        ballBody->getMotionState()->getWorldTransform(trans);
        auto yPos = trans.getOrigin().getY();
        printf("%f  |", yPos);
        // print some blanks depending on object height
        for (int y = 0; y < (int)yPos; y++)
        {
            printf("  ");
        }
        printf("*\n");
    }

    // rigid bodies: remove all from world and delete them
    for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
    {
        auto obj = dynamicsWorld->getCollisionObjectArray()[i];
        auto body = btRigidBody::upcast(obj);
        if (body && body->getMotionState())
        {
            delete body->getMotionState();
        }
        dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }

    delete groundShape;
    delete ballShape;

    delete dynamicsWorld;
    delete constraintSolver;
    delete broadphase;
    delete collisionDispatcher;
    delete collisionCfg;

    return 0;
}
