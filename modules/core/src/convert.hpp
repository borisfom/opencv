




namespace cv
{
#if CV_FP16_TYPE || __CUDA_ARCH__
    inline float16 convertFp32toFp16SW(float a)
{
    return float16(a);
}
    inline float convertFp16toFp32SW(const float16& fp16);
{
    return float(fp16);
}
#else
    float convertFp16toFp32SW(const float16& fp16);
    float16 convertFp32toFp16SW(float fp32);
#endif

namespace opt_FP16
{
    void cvtScale_SIMD32f16f( const float* src, size_t sstep, float16* dst, size_t dstep, cv::Size size, float scale, float shift  );
    void cvtScale_SIMD16f32f( const float16* src, size_t sstep, float* dst, size_t dstep, cv::Size size, float scale, float shift  );
}
namespace opt_AVX2
{
void cvtScale_s16s32f32Line_AVX2(const short* src, int* dst, float scale, float shift, int width);
}
namespace opt_SSE4_1
{
    int cvtScale_SIMD_u8u16f32_SSE41(const uchar * src, ushort * dst, int width, float scale, float shift);
    int cvtScale_SIMD_s8u16f32_SSE41(const schar * src, ushort * dst, int width, float scale, float shift);
    int cvtScale_SIMD_u16u16f32_SSE41(const ushort * src, ushort * dst, int width, float scale, float shift);
    int cvtScale_SIMD_s16u16f32_SSE41(const short * src, ushort * dst, int width, float scale, float shift);
    int cvtScale_SIMD_s32u16f32_SSE41(const int * src, ushort * dst, int width, float scale, float shift);
    int cvtScale_SIMD_f32u16f32_SSE41(const float * src, ushort * dst, int width, float scale, float shift);
    int cvtScale_SIMD_f64u16f32_SSE41(const double * src, ushort * dst, int width, float scale, float shift);
    int Cvt_SIMD_f64u16_SSE41(const double * src, ushort * dst, int width);
}
}