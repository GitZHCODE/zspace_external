#pragma once

#include <headers/zInterface/functionsets/zFnMesh.h>
#include <headers/zApp/include/zFnSets.h>
#include <headers/zApp/include/zInterOp.h>

#include <vector>

namespace zSpace
{
    class zSMin
    {
    public:
        zSMin() {};
        ~zSMin() {};

        enum MODE { 
            min, 
            exponential, 
            root, 
            sigmoid, 
            polynomial_quadratic, 
            polynomial_cubic, 
            polynomial_quartic, 
            circular, 
            circular_geometrical 
        };

        void smin(
            const zScalarArray& a,
            const zScalarArray& b,
            zScalarArray& result,
            float k,
            MODE mode = MODE::min
        );

        void smin_exponential_weighted(
            const zScalarArray& a,
            const zScalarArray& b,
            zScalarArray& result,
            float k,
            float wt
        );

        void smin_multiple(
            const std::vector<zScalarArray>& inputs,
            zScalarArray& result,
            float k,
            MODE mode = MODE::min
        );

        MODE selectMode(
            int mode
        ) {
            switch (mode)
            {
            case 0: return MODE::min;
            case 1: return MODE::exponential;
            case 2: return MODE::root;
            case 3: return MODE::sigmoid;
            case 4: return MODE::polynomial_quadratic;
            case 5: return MODE::polynomial_cubic;
            case 6: return MODE::polynomial_quartic;
            case 7: return MODE::circular;
            case 8: return MODE::circular_geometrical;
            default: return MODE::min;
            }
        };

    private:
        // SMIN Helper Functions declarations
        inline float smin_exponential(float a, float b, float k);
        inline float smin_exponential_wt(float a, float b, float k, float wt);
        inline float smin_root(float a, float b, float k);
        inline float smin_sigmoid(float a, float b, float k);
        inline float smin_polyQuadratic(float a, float b, float k);
        inline float smin_polyCubic(float a, float b, float k);
        inline float smin_polyQuartic(float a, float b, float k);
        inline float smin_circular(float a, float b, float k);
        inline float smin_circularGeometrical(float a, float b, float k);
    };
} 