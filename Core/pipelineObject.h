#ifndef PIPELINE_OBJECT_H
#define PIPELINE_OBJECT_H


//TODO: This is going to be essentially all the state regarding fixed function and a struct for it
//then I want an interface to write it out to binary and consume it in the renderer. 
// maybe also have the shader load info here?
// as well as possible pass info? might be handy
enum blendFactor{
    BLEND_ONE,
    BLEND_ZERO,
    BLEND_SRC_COLOR,
    BLEND_ONE_MINUS_SRC_COLOR,
    BLEND_DST_COLOR,
    BLEND_ONE_MINUS_DST_COLOR,
};
enum blendFactorAlpha{
    BLEND_SRC_ALPHA,
    BLEND_DST_ALPHA,
    BLEND_ONE_MINUS_SRC_ALPHA,
    BLEND_ONE_MINUS_DST_ALPHA,
};
//TODO: figure out why this seems way smaller than it should
enum blendOp{
    BLEND_OP_ADD,
    BLEND_OP_SUB
};

enum polyMode{
    MODE_FILL,
    MODE_LINE,
    MODE_POINT
};
enum cullMode{
    CULL_NONE,
    CULL_BACK,
    CULL_FRONT
};

struct graphicsPipelineState
{
    blendFactor mBlendMode;
    blendOp mBlendOp;
    polyMode mPolyMode;
    cullMode mCullMode;

    //TODO: figure out a default material? does mat own this?
    //TODO: figure out if these should be part this?
    //depth target?
    //render target list?

    //TODO: create render equivalent pointer (composition)
    //TODO: figure out if I can bind the shaders together
    //fragment shader?
    //vertex shader?

};



#endif
