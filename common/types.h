#ifndef TYPES_H_
#define TYPES_H_

#include <iostream>
#include <string>
#include <time.h>
#include <unistd.h>
#include <algorithm>
#include <fstream>
#include <streambuf>
#include <string.h>
#ifndef TFLITE_BUILD
#include "half.hpp"
#endif

// using half_float;

#ifdef TFLITE_BUILD
namespace LowPrecision{
#endif

typedef enum : uint64_t {
    // Status
    Success                 = 0x000000000000,
    AlreadyInitialized      = 0x000000000001,
    SizesMisMatch           = 0x000000000002,
    DimensionsMisMatch      = 0x000000000004,
    Incompelete             = 0x000000000008,
    NotImplemented          = 0x000000000010,
    WrongMethod             = 0x000000000020,
    WrongDataType           = 0x000000000040,
    WrongMemLayout          = 0x000000000080,
    NotInitialized          = 0x000000000100,
    NotAllocated            = 0x000000000200,
    NotFilled               = 0x000000000400,
    NotExtracted            = 0x000000000800,
    NotSupported            = 0x000000001000,
    NotUpdated              = 0x000000002000,
    LHSNotReady             = 0x000000004000,
    RHSNotReady             = 0x000000008000,
    DSTNotReady             = 0x000000010000,
    LHSNotInitialized       = 0x000000020000,
    RHSNotInitialized       = 0x000000040000,
    DSTNotInitialized       = 0x000000080000,
    NotNeeded               = 0x000000100000,
    NeedDowncastWScratch    = 0x000000200000,
    InputsSignsDifferent    = 0x000000400000,
    DSTCantBeUnsigned       = 0x000000800000,
    NeedPackingScratchpad   = 0x000001000000,
    NeedPaddingScratchpad   = 0x000002000000,
    LHSFinalShapeNotValid   = 0x000004000000,
    RHSFinalShapeNotValid   = 0x000008000000,
    DSTFinalShapeNotValid   = 0x000010000000,
    // Source
    InputQuantizition       = 0x000100000000,
    FilterQuantizition      = 0x000200000000,
    SingleMultiply          = 0x000400000000,
    MultiMultiply           = 0x000800000000,
    MultiMultiplyBlock      = 0x001000000000,
    Multiply                = 0x002000000000,
    MulAPI                  = 0x004000000000,
    ApplyDowncast           = 0x008000000000,
    DepadMatrix             = 0x010000000000,
    PreparingFilter         = 0x020000000000,
    PreparingInput          = 0x040000000000,
    PreparingOutput         = 0x080000000000,
    PostprocessingOutput    = 0x100000000000,
    GEMMAPI                 = 0x200000000000,
    // Utility
    MaskOutSource           = 0x0000ffffffff,
    MaskOutStatus           = 0xffff00000000,
} Status;

inline Status mask_out_source(Status input_status){ return (Status)(((uint64_t)input_status) & (uint64_t)Status::MaskOutSource); }
inline Status mask_out_status(Status input_status){ return (Status)(((uint64_t)input_status) & (uint64_t)Status::MaskOutStatus); }
inline const char* get_status_string(Status status){
    char* output = new char[30];
    switch (status)
    {
    case Success:
        strcpy(output, std::string("Success").c_str());
        break;
    case AlreadyInitialized:
        strcpy(output, std::string("AlreadyInitialized").c_str());
        break;
    case SizesMisMatch:
        strcpy(output, std::string("SizesMisMatch").c_str());
        break;
    case DimensionsMisMatch:
        strcpy(output, std::string("DimensionsMisMatch").c_str());
        break;
    case Incompelete:
        strcpy(output, std::string("Incompelete").c_str());
        break;
    case NotImplemented:
        strcpy(output, std::string("NotImplemented").c_str());
        break;
    case WrongMethod:
        strcpy(output, std::string("WrongMethod").c_str());
        break;
    case WrongDataType:
        strcpy(output, std::string("WrongDataType").c_str());
        break;
    case WrongMemLayout:
        strcpy(output, std::string("WrongMemLayout").c_str());
        break;
    case NotInitialized:
        strcpy(output, std::string("NotInitialized").c_str());
        break;
    case NotAllocated:
        strcpy(output, std::string("NotAllocated").c_str());
        break;
    case NotFilled:
        strcpy(output, std::string("NotFilled").c_str());
        break;
    case NotExtracted:
        strcpy(output, std::string("NotExtracted").c_str());
        break;
    case NotSupported:
        strcpy(output, std::string("NotSupported").c_str());
        break;
    case NotUpdated:
        strcpy(output, std::string("NotUpdated").c_str());
        break;
    case LHSNotReady:
        strcpy(output, std::string("LHSNotReady").c_str());
        break;
    case RHSNotReady:
        strcpy(output, std::string("RHSNotReady").c_str());
        break;
    case DSTNotReady:
        strcpy(output, std::string("DSTNotReady").c_str());
        break;
    case LHSNotInitialized:
        strcpy(output, std::string("LHSNotInitialized").c_str());
        break;
    case RHSNotInitialized:
        strcpy(output, std::string("RHSNotInitialized").c_str());
        break;
    case DSTNotInitialized:
        strcpy(output, std::string("DSTNotInitialized").c_str());
        break;
    case NotNeeded:
        strcpy(output, std::string("NotNeeded").c_str());
        break;
    case NeedDowncastWScratch:
        strcpy(output, std::string("NeedDowncastWScratch").c_str());
        break;
    case InputsSignsDifferent:
        strcpy(output, std::string("InputsSignsDifferent").c_str());
        break;
    case DSTCantBeUnsigned:
        strcpy(output, std::string("DSTCantBeUnsigned").c_str());
        break;
    case NeedPackingScratchpad:
        strcpy(output, std::string("NeedPackingScratchpad").c_str());
        break;
    case NeedPaddingScratchpad:
        strcpy(output, std::string("NeedPaddingScratchpad").c_str());
        break;
    case LHSFinalShapeNotValid:
        strcpy(output, std::string("LHSFinalShapeNotValid").c_str());
        break;
    case RHSFinalShapeNotValid:
        strcpy(output, std::string("RHSFinalShapeNotValid").c_str());
        break;
    case DSTFinalShapeNotValid:
        strcpy(output, std::string("DSTFinalShapeNotValid").c_str());
        break;
    case InputQuantizition:
        strcpy(output, std::string("InputQuantizition").c_str());
        break;
    case FilterQuantizition:
        strcpy(output, std::string("FilterQuantizition").c_str());
        break;
    case SingleMultiply:
        strcpy(output, std::string("SingleMultiply").c_str());
        break;
    case MultiMultiply:
        strcpy(output, std::string("MultiMultiply").c_str());
        break;
    case Multiply:
        strcpy(output, std::string("Multiply").c_str());
        break;
    case MulAPI:
        strcpy(output, std::string("MulAPI").c_str());
        break;
    case ApplyDowncast:
        strcpy(output, std::string("ApplyDowncast").c_str());
        break;
    case DepadMatrix:
        strcpy(output, std::string("DepadMatrix").c_str());
        break;
    case PreparingFilter:
        strcpy(output, std::string("PreparingFilter").c_str());
        break;
    case PreparingInput:
        strcpy(output, std::string("PreparingInput").c_str());
        break;
    case PreparingOutput:
        strcpy(output, std::string("PreparingOutput").c_str());
        break;
    case PostprocessingOutput:
        strcpy(output, std::string("PostprocessingOutput").c_str());
        break;
    case GEMMAPI:
        strcpy(output, std::string("GEMMAPI").c_str());
        break;
    default:
        strcpy(output, std::string("NoSuchStatus").c_str());
        break;
    }
    return output;
}
inline Status report_on_failure(Status status, long int id = -1, std::string operator_type = ""){
    if (LowPrecision::mask_out_source(status) != LowPrecision::Status::Success)
        std::cout << "Source: "
                  << LowPrecision::get_status_string(LowPrecision::mask_out_status(status))
                  << " | Status: "
                  << LowPrecision::get_status_string(LowPrecision::mask_out_source(status))
                  << ((id >= 0)?(std::string(" With ID: ") + std::to_string(id)):(""))
                  << ((operator_type != "")?(std::string(" (Operator: ") + operator_type + " )"):(""))
                  << std::endl;
    return status;
}

typedef enum {
    LogMultiplication = 0x01,
    FloatMultiplication = 0x02
} Flags;

typedef enum {
    NoVerbose = 0,
    TimeOnly  = 1,
    Time      = 2,
    Full      = 3
} VerboseLevel;

inline VerboseLevel verbose_level_number_to_value(int x){
    if(x==0)
        return VerboseLevel::NoVerbose;
    if(x==1)
        return VerboseLevel::TimeOnly;
    if(x==2)
        return VerboseLevel::Time;
    if(x==3)
        return VerboseLevel::Full;
    return VerboseLevel::Full;
}

typedef enum {
    VerySmall   = -2,
    Smaller     = -1,
    Small       = 0,
    Medium      = 1,
    Large       = 2
} MatrixSize;

inline MatrixSize matrix_size_number_to_value(int x){
    if(x==-2)
        return MatrixSize::VerySmall;
    if(x==-1)
        return MatrixSize::Smaller;
    if(x==0)
        return MatrixSize::Small;
    if(x==1)
        return MatrixSize::Medium;
    if(x==2)
        return MatrixSize::Large;
    return MatrixSize::Large;
}

typedef enum {
    kNoOptimization                 = 0x000000000000,
    kLogMultiplication              = 0x000000000001,
    kFloatMultiplication            = 0x000000000002,
    kHybridFusedLogMultiplication   = 0x000000000004,
    kFloatRuyMultiplication         = 0x000000000008,
    kLogFusedMultiplication         = 0x000000000010,
    kInt8Multiplication             = 0x000000000020,
    kInt8Shift                      = 0x000000000040,
    kInt8Binary                     = 0x000000000080,
    kFloat32Binary                  = 0x000000000100,
    kFloat16Binary                  = 0x000000000200,
    kInt8Ternary                    = 0x000000000400,
    kFloat32Ternary                 = 0x000000000800,
    kFloat16Ternary                 = 0x000000001000,
    kInt8QuaTernary                 = 0x000000002000,
    kInt8Int4                       = 0x000000004000,
    kInt8ShiftInt4                  = 0x000000008000,
    kInt4ActInt8Weight              = 0x000000010000,
    kInt4ActInt4Weight              = 0x000000020000,
    kTernaryActInt8Weight           = 0x000000040000,
    kTernaryActTernaryWeight        = 0x000000080000,
    kBinaryActInt8Weight            = 0x000000100000,
    kBinaryActBinaryWeight          = 0x000000200000,
    kBinaryActBinaryWeightXOR       = 0x000000400000,
    kInt3ActInt3Weight              = 0x000000800000,
    kInt8ActInt4PowerWeights        = 0x000001000000,
    kULPPACK                        = 0x0000fe000000,
    kULPPACKW1A1                    = 0x000002000000,
    kULPPACKW2A2                    = 0x000004000000,
    kULPPACKW3A3                    = 0x000008000000,
    kULPPACKW4A4                    = 0x000010000000,
    kULPPACKW5A5                    = 0x000020000000,
    kULPPACKW6A6                    = 0x000040000000,
    kULPPACKW7A7                    = 0x000080000000,
    k8x8                            = 0x0020fe000000,
    kSelfDependent                  = 0x001e00000000,
    kSelfDependentW4A4              = 0x000200000000,
    kSelfDependentW4A8              = 0x000400000000,
    kSelfDependentW8A4              = 0x000800000000,
    kSelfDependentW2A2              = 0x001000000000,
    kBarrelShiftMul                 = 0x03e000000000,
    kBarrelShiftMulW8A8             = 0x002000000000,
    kBarrelShiftMulW4A4             = 0x004000000000,
    kBarrelShiftMulW4A8             = 0x008000000000,
    kBarrelShiftMulW8A4             = 0x010000000000,
    kBarrelShiftMulW2A2             = 0x020000000000,
} Method;

inline const char* get_method_string(Method method){
    char* output = new char[60];
    switch (method)
    {
    case kNoOptimization:
        strcpy(output, std::string("NoOptimization").c_str());
        break;
    case kLogMultiplication:
        strcpy(output, std::string("LogMultiplication").c_str());
        break;
    case kFloatMultiplication:
        strcpy(output, std::string("FloatMultiplication").c_str());
        break;
    case kHybridFusedLogMultiplication:
        strcpy(output, std::string("HybridFusedLogMultiplication").c_str());
        break;
    case kFloatRuyMultiplication:
        strcpy(output, std::string("FloatRuyMultiplication").c_str());
        break;
    case kLogFusedMultiplication:
        strcpy(output, std::string("LogFusedMultiplication").c_str());
        break;
    case kInt8Multiplication:
        strcpy(output, std::string("Int8Multiplication").c_str());
        break;
    case kInt8Shift:
        strcpy(output, std::string("Int8Shift").c_str());
        break;
    case kInt8Binary:
        strcpy(output, std::string("Int8Binary").c_str());
        break;
    case kFloat32Binary:
        strcpy(output, std::string("Float32Binary").c_str());
        break;
    case kFloat16Binary:
        strcpy(output, std::string("Float16Binary").c_str());
        break;
    case kInt8Ternary:
        strcpy(output, std::string("Int8Ternary").c_str());
        break;
    case kFloat32Ternary:
        strcpy(output, std::string("Float32Ternary").c_str());
        break;
    case kFloat16Ternary:
        strcpy(output, std::string("Float16Ternary").c_str());
        break;
    case kInt8QuaTernary:
        strcpy(output, std::string("Int8QuaTernary").c_str());
        break;
    case kInt8Int4:
        strcpy(output, std::string("Int8Int4").c_str());
        break;
    case kInt8ShiftInt4:
        strcpy(output, std::string("Int8ShiftInt4").c_str());
        break;
    case kInt4ActInt8Weight:
        strcpy(output, std::string("Int4ActInt8Weight").c_str());
        break;
    case kInt4ActInt4Weight:
        strcpy(output, std::string("Int4ActInt4Weight").c_str());
        break;
    case kTernaryActInt8Weight:
        strcpy(output, std::string("TernaryActInt8Weight").c_str());
        break;
    case kTernaryActTernaryWeight:
        strcpy(output, std::string("TernaryActTernaryWeight").c_str());
        break;
    case kBinaryActInt8Weight:
        strcpy(output, std::string("BinaryActInt8Weight").c_str());
        break;
    case kBinaryActBinaryWeight:
        strcpy(output, std::string("BinaryActBinaryWeight").c_str());
        break;
    case kInt3ActInt3Weight:
        strcpy(output, std::string("Int3ActInt3Weight").c_str());
        break;
    case kInt8ActInt4PowerWeights:
        strcpy(output, std::string("Int8ActInt4PowerWeights").c_str());
        break;
    case kULPPACK:
        strcpy(output, std::string("ULPPACK").c_str());
        break;
    case kULPPACKW1A1:
        strcpy(output, std::string("ULPPACKW1A1").c_str());
        break;
    case kULPPACKW2A2:
        strcpy(output, std::string("ULPPACKW2A2").c_str());
        break;
    case kULPPACKW3A3:
        strcpy(output, std::string("ULPPACKW3A3").c_str());
        break;
    case kULPPACKW4A4:
        strcpy(output, std::string("ULPPACKW4A4").c_str());
        break;
    case kULPPACKW5A5:
        strcpy(output, std::string("ULPPACKW5A5").c_str());
        break;
    case kULPPACKW6A6:
        strcpy(output, std::string("ULPPACKW6A6").c_str());
        break;
    case kULPPACKW7A7:
        strcpy(output, std::string("ULPPACKW7A7").c_str());
        break;
    case k8x8:
        strcpy(output, std::string("8x8").c_str());
        break;
    case kSelfDependentW4A4:
        strcpy(output, std::string("SelfDependentW4A4").c_str());
        break;
    case kSelfDependentW4A8:
        strcpy(output, std::string("SelfDependentW4A8").c_str());
        break;
    case kSelfDependentW8A4:
        strcpy(output, std::string("SelfDependentW8A4").c_str());
        break;
    case kSelfDependentW2A2:
        strcpy(output, std::string("SelfDependentW2A2").c_str());
        break;
    case kBarrelShiftMulW8A8:
        strcpy(output, std::string("BarrelShiftMulW8A8").c_str());
        break;
    case kBarrelShiftMulW4A4:
        strcpy(output, std::string("BarrelShiftMulW4A4").c_str());
        break;
    case kBarrelShiftMulW4A8:
        strcpy(output, std::string("BarrelShiftMulW4A8").c_str());
        break;
    case kBarrelShiftMulW8A4:
        strcpy(output, std::string("BarrelShiftMulW8A4").c_str());
        break;
    case kBarrelShiftMulW2A2:
        strcpy(output, std::string("BarrelShiftMulW2A2").c_str());
        break;
    default:
        strcpy(output, std::string("NotDefined").c_str());
        break;
    }
    return output;
}

typedef enum {
    kRowMajor,
    kColumnMajor,
} MemLayout;

typedef enum {
    Float32,
    Float16,
    Int32,
    Int16,
    Int8,
    Int4,
    Bool,
    NotAvailable
} DataType;

typedef enum {
    kMultiBatch = 0x01,
    kSingleBatch = 0x02
} BatchesMode;

typedef enum {
    Input,
    Weight,
    Output,
    Unknown,
} MatrixType;

typedef enum {
    Nothing             = 0x0,
    PaddingIfNeccessery = 0x1,
    Packing             = 0x2,
    PaddingAndPacking   = 0x3,
} PreprocessType;

typedef enum {
    SupportsNothing         = 0x0,
    SupportsGEMV            = 0x1,
    SupportsGEMM            = 0x2,
    SupportsGEMMAndGEMV     = 0x3,
    SupportsBlockProcessing = 0x4,
} GEMMType;

typedef enum {
    NotSelfDependent            = 0x000000,
    // Int1
    W1A1SelfDependent           = 0x000101,
    W1A8SelfDependent           = 0x000100,
    W8A1SelfDependent           = 0x000001,
    // Int2
    W2A2SelfDependent           = 0x000202,
    W2A8SelfDependent           = 0x000200,
    W8A2SelfDependent           = 0x000002,
    // Int4
    W4A4SelfDependent           = 0x000404,
    W4A8SelfDependent           = 0x000400,
    W8A4SelfDependent           = 0x000004,
    // With 16 Offset
    // Int1 16 Offset
    W1A1SelfDependent16Offset   = 0x010101,
    W1A8SelfDependent16Offset   = 0x010100,
    W8A1SelfDependent16Offset   = 0x010001,
    // Int2 16 Offset
    W2A2SelfDependent16Offset   = 0x010202,
    W2A8SelfDependent16Offset   = 0x010200,
    W8A2SelfDependent16Offset   = 0x010002,
    // Int4 16 Offset
    W4A4SelfDependent16Offset   = 0x010404,
    W4A8SelfDependent16Offset   = 0x010400,
    W8A4SelfDependent16Offset   = 0x010004,
} SelfDependentType;

inline int get_self_dependent_A_num_shifts(SelfDependentType type){ return type & 0x0000ff; }
inline int get_self_dependent_W_num_shifts(SelfDependentType type){ return (type & 0x00ff00) >> 8; }
inline int get_self_dependent_A_data_count(SelfDependentType type){ return 8 / (type & 0x00000f); }
inline int get_self_dependent_W_data_count(SelfDependentType type){ return 8 / ((type & 0x000f00) >> 8); }

inline int get_self_dependent_offset(SelfDependentType type){ 
    switch ((type & 0xff0000) >> 16){
    case 0:
        return 1;
    case 1:
        return 16;
    default:
        return 0;
    } 
}

typedef union {
  float f;
  struct {
    unsigned int mantisa : 23;
    unsigned int exponent : 8;
    unsigned int sign : 1;
  } parts;
} Float;

class Shape
{
    long int id;
    bool initilizied = false;
    bool allocated = false;
public:
    static unsigned long int last_id;
    size_t number_dims;
    int* size;
    size_t flatsize;

    Shape():number_dims(0),size(nullptr),flatsize(0){id = last_id; last_id++;}
    ~Shape(){
        this->initilizied = false;
        delete[] this->size;
        this->allocated = false;
    }
    Shape(const Shape& reference){
        this->id = last_id;
        last_id++;
        this->number_dims = reference.number_dims;
        this->flatsize = reference.flatsize;
        this->size = new int[reference.number_dims];
        this->allocated = true;
        for (int i = 0 ; i < reference.number_dims ; i++)
            this->size[i] = reference.size[i];
        this->initilizied = true;
    }
    long int get_id(){return id;}
    void extend_dims(bool as_highest_dim=true){
        number_dims++;
        int* old_size = size;
        size = new int[number_dims];
        this->allocated = true;
        if(as_highest_dim){
            size[0] = 1;
            for (int i = 1; i < number_dims; i++)
                size[i] = old_size[i - 1];
            this->initilizied = true;
        }
        else{
            size[number_dims - 1] = 1;
            for (int i = 0; i < number_dims - 1; i++)
                size[i] = old_size[i];
            this->initilizied = true;
        }
    }
    Shape& operator=(const Shape& other){
        this->id = last_id;
        last_id++;
        this->number_dims = other.number_dims;
        this->flatsize = other.flatsize;
        this->size = new int[other.number_dims];
        this->allocated = true;
        for (int i = 0 ; i < other.number_dims ; i++)
            this->size[i] = other.size[i];
        this->initilizied = true;
        return *this;
    }
    bool operator==(const Shape& other){
        if (this->number_dims != other.number_dims)
            return false;
        bool isEqual = true;
        for (int i = 0 ; i < number_dims ; i++)
            isEqual &= this->size[i] == other.size[i];
        return isEqual;
    }
    bool operator!=(const Shape& other){
        if (this->number_dims != other.number_dims)
            return true;
        bool isEqual = true;
        for (int i = 0 ; i < number_dims ; i++)
            isEqual &= this->size[i] == other.size[i];
        return !isEqual;
    }
    static inline bool Validate(const Shape& shape){
        if (shape.flatsize == 0) return false;
        else if (!shape.initilizied) return false;
        else if (!shape.allocated) return false;
        else if (shape.number_dims == 0) return false;
        else if (shape.size == nullptr) return false;
        else return true;
    }
    Shape T(){
        Shape shape;
        shape.flatsize = flatsize;
        shape.number_dims = number_dims;
        shape.size = new int[shape.number_dims];
        shape.allocated = true;
        for (size_t i = 0 ; i < number_dims ; i++)
            shape.size[number_dims - 1 - i] = size[i];
        shape.initilizied = true;
        return shape;
    }
};

typedef struct {
    float first;
    float second;
    float third;
    float fourth;
} Float4x;

#ifndef TFLITE_BUILD
typedef half_float::half float16;
#endif

template <typename T>
T* allocate(size_t size){
    return new T[size];
}

template <typename T>
T** allocate2D(size_t first_size, size_t second_size){
    T** result = new T*[first_size];
    for(size_t i; i < first_size; i++)
        result[i] = new T[second_size];
    return result;
}

template <typename T>
void deallocate(T* array, bool is_array = true){
    if(is_array)
        delete[] array;
    else
        delete array;
}

template<typename T, typename S>
inline T* get_pointer_as(S* pointer){ return (T*) pointer;}
template<typename T, typename S>
inline T get_as(S value){ return *((T*)(&value));}

template<typename T>
inline void zero_vector(T* array, int n){for(int i=0;i<n;i++) array[i] = 0;}

template<typename T>
inline void one_vector(T* array, int n){for(int i=0;i<n;i++) array[i] = 1;}
template<typename T>
inline void minus_one_vector(T* array, int n){for(int i=0;i<n;i++) array[i] = -1;}
template<typename T>
inline void one_minus_one_vector(T* array, int n){for(int i=0;i<n;i++) array[i] = (i%2)?(-1):(1);}

template<typename T>
inline void two_vector(T* array, int n){for(int i=0;i<n;i++) array[i] = 2;}
template<typename T>
inline void minus_two_vector(T* array, int n){for(int i=0;i<n;i++) array[i] = -2;}
template<typename T>
inline void two_minus_two_vector(T* array, int n){for(int i=0;i<n;i++) array[i] = (i%2)?(-2):(2);}

template<typename T>
inline void half_one_half_zero_vector(T* array, int n){for(int i=0;i<n;i++) array[i] = (i<(n/2))?(1):(0);}


inline Shape get_shape(int* in_shape, int n){
    // #ifndef TFLITE_BUILD
    // if (n < 1 || n > 3)
    //     throw std::string("Can not construct shapes with lower than 0 dimensions or more than 3.");
    // #else
    // if (n < 1 || n > 3){
    //     Shape shape;
    //     shape.number_dims = 0;
    //     shape.size = new int[1];
    //     shape.size[0] = 0;
    //     shape.flatsize = 0;
    //     return shape;
    // }
    // #endif
    Shape shape;
    shape.number_dims = n;
    shape.flatsize = 1;
    shape.size = new int[n];
    for (int i = 0; i < n; i++){
        shape.size[i] = in_shape[i];
        shape.flatsize *= shape.size[i];
    }
    return shape;
}

inline Shape create_shape(int* in_shape, int n){
    #ifndef TFLITE_BUILD
    if (n < 1 || n > 3)
        throw std::string("Can not construct shapes with lower than 0 dimensions or more than 3.");
    #else
    if (n < 1 || n > 3){
        Shape shape;
        shape.number_dims = 0;
        shape.size = new int[1];
        shape.size[0] = 0;
        shape.flatsize = 0;
        return shape;
    }
    #endif
    Shape shape;
    shape.number_dims = n;
    shape.flatsize = 1;
    shape.size = new int[n];
    for (int i = 0; i < n; i++){
        shape.size[i] = in_shape[i];
        shape.flatsize *= shape.size[i];
    }
    return shape;
}

inline std::string get_shape_string(Shape shape){
    std::string str = "(";
    for (int i = 0; i < shape.number_dims; i++)
        str += std::to_string(shape.size[i]) + ", ";
    str += ")";
    return str;
}

inline long double calculate_time_diff_seconds(timespec start, timespec end){
    long double tstart_ext_ld, tend_ext_ld, tdiff_ext_ld;
	tstart_ext_ld = (long double)start.tv_sec + start.tv_nsec/1.0e+9;
	tend_ext_ld = (long double)end.tv_sec + end.tv_nsec/1.0e+9;
	tdiff_ext_ld = (long double)(tend_ext_ld - tstart_ext_ld);
    return tdiff_ext_ld;
}

template<typename T>
inline Status get_absed_max_min(T* array, int length, T& max, T& min){
    if (length <= 0)
        return Status::SizesMisMatch;
    max = array[0];
    min = array[0];
    if (length == 1){
        return Status::Success;
    }
    auto o = std::minmax_element(array, array + length);
    T min_n = *o.first;
    T max_n = *o.second;
    if (min_n < 0 && max_n < 0){
        max = -min_n;
        min = -max_n;
    }
    else if (min_n >= 0 && max_n >= 0){
        max = max_n;
        min = min_n;
    }
    else if (min_n < 0 && max_n >= 0){
        max = std::max(max_n, -min_n);
        min = 0;
    }
    return Status::Success;
}

template<typename T>
inline LowPrecision::Status transpose(T* input, T* output, LowPrecision::Shape original_shape){
    if (original_shape.number_dims != 2)
        return LowPrecision::Status::NotSupported;
    size_t p = 0;
    for (size_t r = 0 ; r < original_shape.size[0] ; r++)
        for (size_t c = 0 ; c < original_shape.size[1] ; c++)
            output[c * original_shape.size[0] + r] = input[p++];
    return LowPrecision::Status::Success;
}

inline bool check_for_fp16_support(){
    std::ifstream t("/proc/cpuinfo");
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    if (str.find("fphp") != std::string::npos)
        return true;
    else
        return false;
}

#ifdef TFLITE_BUILD
}
#endif

#endif