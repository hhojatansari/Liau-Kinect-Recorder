#ifndef STRUCTBODY_H
#define STRUCTBODY_H


class StructBody
{
public:
    StructBody();
    struct JointBody{
        bool trackingState[24];
        float X[24];
        float Y[24];
        float Z[24];
        int xColor[24];
        int yColor[24];
    }joint;
};

#endif // STRUCTBODY_H
