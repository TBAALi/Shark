#include <shark/Data/Dataset.h>
#include <shark/Core/Random.h>
#include <shark/Algorithms/Trainers/NormalizeKernelUnitVariance.h>
#include <shark/Models/Kernels/GaussianRbfKernel.h>
#include <shark/Models/Kernels/WeightedSumKernel.h>
#include <shark/Models/Kernels/SubrangeKernel.h>
#include <shark/Models/Kernels/MklKernel.h>
#include <shark/Models/Kernels/LinearKernel.h>
#include <shark/Models/Kernels/DiscreteKernel.h>
#include <shark/Models/Kernels/PolynomialKernel.h>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/include/as_vector.hpp>

        struct HeterogeneousInputStruct{
        shark::RealVector rv1;
        std::size_t st2;
        shark::RealVector crv3;
    };

    #ifndef DOXYGEN_SHOULD_SKIP_THIS
        BOOST_FUSION_ADAPT_STRUCT(
            HeterogeneousInputStruct,
            (shark::RealVector, rv1)(std::size_t, st2)(shark::RealVector, crv3)
        )
    #endif /* DOXYGEN_SHOULD_SKIP_THIS */

    namespace shark{
        template<>
        struct Batch< HeterogeneousInputStruct >{
            SHARK_CREATE_BATCH_INTERFACE_NO_TPL(
                HeterogeneousInputStruct,
                (shark::RealVector, rv1)(std::size_t, st2)(shark::RealVector, crv3)
            )
        };
    }
    
using namespace shark;
using namespace std;




int main(int argc, char** argv)
{

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

        // test points
    RealVector x1(2);
    x1(0)=2;
    x1(1)=1;
    RealVector x2(2);
    x2(0)=-2;
    x2(1)=1;
    

        // initialize kernels
    DenseRbfKernel baseKernel1( 0.1 );
    DenseRbfKernel baseKernel2( 0.01 );
    std::vector< AbstractKernelFunction<RealVector> * > kernels1;
    kernels1.push_back( &baseKernel1 );
    kernels1.push_back( &baseKernel2 );
    DenseWeightedSumKernel kernel1( kernels1 );
    
////////////////////////////////////////////////////////////////////////////////

        // examine initial state
    std::cout << endl << " ======================= WeightedSumKernel: ======================= " << std::endl;
    cout << endl << "kernel1.isAdaptive(0): " << kernel1.isAdaptive(0) << endl;
    cout << "kernel1.isAdaptive(1): " << kernel1.isAdaptive(1) << endl;
    cout << "kernel1.numberOfParameters(): " << kernel1.numberOfParameters() << endl;
    cout << "kernel1.parameterVector(): " << kernel1.parameterVector() << endl;
    cout << "kernel1.eval(x1,x2): " << kernel1.eval(x1,x2) << endl << endl;
    
        // change something
    RealVector new_params_1( kernel1.numberOfParameters() );
    new_params_1(0) = 1.0;
    kernel1.setParameterVector( new_params_1 );
    
        // examine again
    cout << "kernel1.parameterVector() with 1st parameter set to 1: " << kernel1.parameterVector() << endl;
    cout << "kernel1.eval(x1,x2): " << kernel1.eval(x1,x2) << endl << endl;
    
        // change something else
    kernel1.setAdaptive(0,true);
    
        // examine once more
    cout << "kernel1.isAdaptive(0): " << kernel1.isAdaptive(0) << endl;
    cout << "kernel1.isAdaptive(1): " << kernel1.isAdaptive(1) << endl;
    cout << "kernel1.numberOfParameters(): " << kernel1.numberOfParameters() << endl;
    cout << "kernel1.parameterVector(): " << kernel1.parameterVector() << endl<< endl;
    
        // another change
    kernel1.setAdaptive(0,false);
    kernel1.setAdaptive(1,true);
    
        // examining again
    cout << "kernel1.isAdaptive(0): " << kernel1.isAdaptive(0) << endl;
    cout << "kernel1.isAdaptive(1): " << kernel1.isAdaptive(1) << endl;
    cout << "kernel1.numberOfParameters(): " << kernel1.numberOfParameters() << endl;
    cout << "kernel1.parameterVector(): " << kernel1.parameterVector() << endl<< endl;
    
        // last change
    kernel1.setAdaptiveAll(true);
    
        // last examination
    cout << "kernel1.isAdaptive(0): " << kernel1.isAdaptive(0) << endl;
    cout << "kernel1.isAdaptive(1): " << kernel1.isAdaptive(1) << endl;
    cout << "kernel1.numberOfParameters(): " << kernel1.numberOfParameters() << endl;
    cout << "kernel1.parameterVector(): " << kernel1.parameterVector() << endl;
    cout << "kernel1.eval(x1,x2): " << kernel1.eval(x1,x2) << endl << endl;
    
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

        DenseRbfKernel baseKernel3(0.1);
    DenseRbfKernel baseKernel4(0.01);
    std::vector<AbstractKernelFunction<RealVector>* > kernels2;
    kernels2.push_back(&baseKernel3);
    kernels2.push_back(&baseKernel4);
    
        std::vector< std::pair< std::size_t, std::size_t > > indcs_1;
    indcs_1.push_back( std::make_pair( 0,2 ) );
    indcs_1.push_back( std::make_pair( 0,2 ) );
    DenseSubrangeKernel kernel2( kernels2, indcs_1 );
    
////////////////////////////////////////////////////////////////////////////////

        // examine initial state
    std::cout << endl << " ======================= SubrangeKernel, full index range: ======================= " << std::endl;
    cout << endl << "kernel2.isAdaptive(0): " << kernel2.isAdaptive(0) << endl;
    cout << "kernel2.isAdaptive(1): " << kernel2.isAdaptive(1) << endl;
    cout << "kernel2.numberOfParameters(): " << kernel2.numberOfParameters() << endl;
    cout << "kernel2.parameterVector(): " << kernel2.parameterVector() << endl;
    cout << "kernel2.eval(x1,x2): " << kernel2.eval(x1,x2) << endl << endl;
    
        // change something
    RealVector new_params_2( kernel2.numberOfParameters() );
    new_params_2(0) = 1.0;
    kernel2.setParameterVector( new_params_2 );
    
        // examine again
    cout << "kernel2.parameterVector() with 1st parameter set to 1: " << kernel2.parameterVector() << endl;
    cout << "kernel2.eval(x1,x2): " << kernel2.eval(x1,x2) << endl << endl;
    
        // change something else
    kernel2.setAdaptive(0,true);
    
        // examine once more
    cout << "kernel2.isAdaptive(0): " << kernel2.isAdaptive(0) << endl;
    cout << "kernel2.isAdaptive(1): " << kernel2.isAdaptive(1) << endl;
    cout << "kernel2.numberOfParameters(): " << kernel2.numberOfParameters() << endl;
    cout << "kernel2.parameterVector(): " << kernel2.parameterVector() << endl<< endl;
    
        // another change
    kernel2.setAdaptive(0,false);
    kernel2.setAdaptive(1,true);
    
        // examining again
    cout << "kernel2.isAdaptive(0): " << kernel2.isAdaptive(0) << endl;
    cout << "kernel2.isAdaptive(1): " << kernel2.isAdaptive(1) << endl;
    cout << "kernel2.numberOfParameters(): " << kernel2.numberOfParameters() << endl;
    cout << "kernel2.parameterVector(): " << kernel2.parameterVector() << endl<< endl;
    
        // last change
    kernel2.setAdaptiveAll(true);
    
        // last examination
    cout << "kernel2.isAdaptive(0): " << kernel2.isAdaptive(0) << endl;
    cout << "kernel2.isAdaptive(1): " << kernel2.isAdaptive(1) << endl;
    cout << "kernel2.numberOfParameters(): " << kernel2.numberOfParameters() << endl;
    cout << "kernel2.parameterVector(): " << kernel2.parameterVector() << endl;
    cout << "kernel2.eval(x1,x2): " << kernel2.eval(x1,x2) << endl << endl;
    

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


        DenseRbfKernel baseKernel5(0.1);
    DenseRbfKernel baseKernel6(0.01);
    std::vector<AbstractKernelFunction<RealVector>* > kernels3;
    kernels3.push_back(&baseKernel5);
    kernels3.push_back(&baseKernel6);
    
        std::vector< std::pair< std::size_t, std::size_t > > indcs_2;
    indcs_2.push_back( std::make_pair( 0,1 ) );
    indcs_2.push_back( std::make_pair( 1,2 ) );
    DenseSubrangeKernel kernel3( kernels3, indcs_2 );
    
////////////////////////////////////////////////////////////////////////////////

        // examine initial state
    std::cout << endl << " ======================= SubrangeKernel partial index range: ======================= " << std::endl;
    cout << endl << "kernel3.isAdaptive(0): " << kernel3.isAdaptive(0) << endl;
    cout << "kernel3.isAdaptive(1): " << kernel3.isAdaptive(1) << endl;
    cout << "kernel3.numberOfParameters(): " << kernel3.numberOfParameters() << endl;
    cout << "kernel3.parameterVector(): " << kernel3.parameterVector() << endl;
    cout << "kernel3.eval(x1,x2): " << kernel3.eval(x1,x2) << endl << endl;
    
        // change something
    RealVector new_params_3( kernel3.numberOfParameters() );
    new_params_3(0) = 1.0;
    kernel3.setParameterVector( new_params_3 );
    
        // examine again
    cout << "kernel3.parameterVector() with 1st parameter set to 1: " << kernel3.parameterVector() << endl;
    cout << "kernel3.eval(x1,x2): " << kernel3.eval(x1,x2) << endl << endl;
    
        // change something else
    kernel3.setAdaptive(0,true);
    
        // examine once more
    cout << "kernel3.isAdaptive(0): " << kernel3.isAdaptive(0) << endl;
    cout << "kernel3.isAdaptive(1): " << kernel3.isAdaptive(1) << endl;
    cout << "kernel3.numberOfParameters(): " << kernel3.numberOfParameters() << endl;
    cout << "kernel3.parameterVector(): " << kernel3.parameterVector() << endl<< endl;
    
        // another change
    kernel3.setAdaptive(0,false);
    kernel3.setAdaptive(1,true);
    
        // examining again
    cout << "kernel3.isAdaptive(0): " << kernel3.isAdaptive(0) << endl;
    cout << "kernel3.isAdaptive(1): " << kernel3.isAdaptive(1) << endl;
    cout << "kernel3.numberOfParameters(): " << kernel3.numberOfParameters() << endl;
    cout << "kernel3.parameterVector(): " << kernel3.parameterVector() << endl<< endl;
    
        // last change
    kernel3.setAdaptiveAll(true);
    
        // last examination
    cout << "kernel3.isAdaptive(0): " << kernel3.isAdaptive(0) << endl;
    cout << "kernel3.isAdaptive(1): " << kernel3.isAdaptive(1) << endl;
    cout << "kernel3.numberOfParameters(): " << kernel3.numberOfParameters() << endl;
    cout << "kernel3.parameterVector(): " << kernel3.parameterVector() << endl;
    cout << "kernel3.eval(x1,x2): " << kernel3.eval(x1,x2) << endl << endl;
    
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


        // set dimensions for data
    std::size_t const num_samples = 2;
    std::size_t const dim_nonzeros = 2;
    std::size_t const max_elem_discr_kernel = 3;
    std::size_t const dim_sparse = 5;
    // create temporary helper container
    std::vector<HeterogeneousInputStruct> data( num_samples );
    // and fill it
    data[0].rv1.resize( dim_nonzeros ); data[0].crv3.resize( dim_sparse); //size 5
    data[1].rv1.resize( dim_nonzeros ); data[1].crv3.resize( dim_sparse); //size 5
    data[0].rv1(0) = 1.0; data[0].rv1(1) = -1.0; data[0].crv3(1) = -0.5; data[0].crv3(4) = 8.0;
    data[1].rv1(0) = 1.0; data[1].rv1(1) = -2.0; data[1].crv3(1) =  1.0; data[1].crv3(3) = 0.1;
    data[0].st2 = 1; data[1].st2 = 2;
    // and use it to create the 'real' dataset
    Data<HeterogeneousInputStruct> dataset = createDataFromRange( data, 10 );
    
////////////////////////////////////////////////////////////////////////////////

        //create state matrix for the discrete kernel. necessary but not so relevant
    RealMatrix matK( max_elem_discr_kernel, max_elem_discr_kernel );
    matK(0,0) = 0.05; matK(1,1) = 1.0;  matK(2,2) = 0.5;
    matK(0,1) = matK(1,0) = 0.2; matK(0,2) = matK(2,0) = 0.4;  matK(1,2) = matK(2,1) = 0.6;
    // set up base kernels
    DenseRbfKernel baseKernelRV1(0.1);
    DiscreteKernel baseKernelST2(matK);
    DenseLinearKernel baseKernelCRV3;
    MklKernel<HeterogeneousInputStruct> mkl_kernel( boost::fusion::make_vector( &baseKernelRV1, &baseKernelST2, &baseKernelCRV3) );
    
        // examine initial state
    std::cout << endl << " ======================= MklKernel: ======================= " << std::endl;
    cout << endl << "mkl_kernel.isAdaptive(0): " << mkl_kernel.isAdaptive(0) << endl;
    cout << "mkl_kernel.isAdaptive(1): " << mkl_kernel.isAdaptive(1) << endl;
    cout << "mkl_kernel.isAdaptive(2): " << mkl_kernel.isAdaptive(2) << endl;
    cout << "mkl_kernel.numberOfParameters(): " << mkl_kernel.numberOfParameters() << endl;
    cout << "mkl_kernel.parameterVector(): " << mkl_kernel.parameterVector() << endl;
    cout << "mkl_kernel.eval( dataset.element(0), dataset.element(1) ): " << mkl_kernel.eval( dataset.element(0), dataset.element(1) ) << endl << endl;
    
        // change something
    mkl_kernel.setAdaptiveAll(true);
    RealVector new_params_4( mkl_kernel.numberOfParameters() );
    new_params_4(0) = 1.0;
    new_params_4(2) = 0.2;
    mkl_kernel.setParameterVector( new_params_4 );
    
        // examine effects
    cout << "mkl_kernel.isAdaptive(0): " << mkl_kernel.isAdaptive(0) << endl;
    cout << "mkl_kernel.isAdaptive(1): " << mkl_kernel.isAdaptive(1) << endl;
    cout << "mkl_kernel.isAdaptive(2): " << mkl_kernel.isAdaptive(2) << endl;
    cout << "mkl_kernel.numberOfParameters(): " << mkl_kernel.numberOfParameters() << endl;
    cout << "mkl_kernel.parameterVector(): " << mkl_kernel.parameterVector() << endl;
    cout << "mkl_kernel.eval( dataset.element(0), dataset.element(1) ): " << mkl_kernel.eval( dataset.element(0), dataset.element(1) ) << endl << endl;
    

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

        std::size_t num_dims = 9;
    std::size_t num_points = 200;
    std::vector<RealVector> input(num_points);
    RealVector v(num_dims);
    for ( std::size_t i=0; i<num_points; i++ ) {
        for ( std::size_t j=0; j<num_dims; j++ )
            v(j) = random::uni(random::globalRng, -1,1);
        input[i] = v;
    }
    UnlabeledData<RealVector> rand_data = createDataFromRange( input );
    

        // declare kernels
    DenseRbfKernel         unnormalized_kernel1(0.1);
    DenseLinearKernel      unnormalized_kernel2;
    DensePolynomialKernel  unnormalized_kernel3(2, 1.0);
    // declare indices
    std::vector< std::pair< std::size_t, std::size_t > > indices;
    indices.push_back( std::make_pair( 0,3 ) );
    indices.push_back( std::make_pair( 3,6 ) );
    indices.push_back( std::make_pair( 6,9 ) );
    
        DenseScaledKernel scale( &unnormalized_kernel3 );
    NormalizeKernelUnitVariance<> normalizer;
    normalizer.train( scale, rand_data );
    

        std::cout << endl << " ======================= Kernel normalization: ======================= " << std::endl;

    std::cout << endl << "Done training. Factor is " << scale.factor() << std::endl;
    std::cout << "Mean                   = " << normalizer.mean() << std::endl;
    std::cout << "Trace                  = " << normalizer.trace() << std::endl << std::endl;
    //check in feature space
    double control = 0.0;
    for ( std::size_t i=0; i<num_points; i++ ) {
        control += scale.eval(input[i], input[i]);
        for ( std::size_t j=0; j<num_points; j++ ) {
            control -= scale.eval(input[i],input[j]) / num_points;
        }
    }
    control /= num_points;
    std::cout << "Resulting variance of scaled Kernel: " << control << std::endl << std::endl;
    
        std::vector<AbstractKernelFunction<RealVector>* > kernels4;
    kernels4.push_back( &unnormalized_kernel1 );
    kernels4.push_back( &unnormalized_kernel2 );
    kernels4.push_back( &scale );
    DenseSubrangeKernel kernel4( kernels4, indices );
    }
