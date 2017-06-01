#include "perf_precomp.hpp"

using namespace std;
using namespace cv;
using namespace perf;
using std::tr1::make_tuple;
using std::tr1::get;

enum { TYPE_5_8 =FastFeatureDetector::TYPE_5_8, TYPE_7_12 = FastFeatureDetector::TYPE_7_12, TYPE_9_16 = FastFeatureDetector::TYPE_9_16 };
CV_ENUM(FastType, TYPE_5_8, TYPE_7_12, TYPE_9_16)

typedef std::tr1::tuple<string, FastType> File_Type_t;
typedef perf::TestBaseWithParam<File_Type_t> fast;

#define FAST_IMAGES \
    "cv/detectors_descriptors_evaluation/images_datasets/leuven/img1.png",\
    "stitching/a3.png"

PERF_TEST_P(fast, detect, testing::Combine(
                            testing::Values(FAST_IMAGES),
                            FastType::all()
                          ))
{
    string filename = getDataPath(get<0>(GetParam()));
    int type = get<1>(GetParam());
    Mat frame = imread(filename, IMREAD_GRAYSCALE);

    if (frame.empty())
        FAIL() << "Unable to load source image " << filename;

    declare.in(frame);

    Ptr<FeatureDetector> fd = FastFeatureDetector::create(20, true, type);
    ASSERT_FALSE( fd.empty() );
    vector<KeyPoint> points;

    TEST_CYCLE() fd->detect(frame, points);

    SANITY_CHECK_KEYPOINTS(points);
}

PERF_TEST_P(fast, detect_ovx, testing::Combine(
    testing::Values(FAST_IMAGES),
    FastType::all()
))
{
    string filename = getDataPath(get<0>(GetParam()));
    int type = get<1>(GetParam());
    Mat frame = imread(filename, IMREAD_GRAYSCALE);

    if (frame.empty())
        FAIL() << "Unable to load source image " << filename;

    declare.in(frame);

    Ptr<FeatureDetector> fd = FastFeatureDetector::create(20, false, type);
    ASSERT_FALSE(fd.empty());
    vector<KeyPoint> points;

    TEST_CYCLE() fd->detect(frame, points);

    SANITY_CHECK_KEYPOINTS(points);
}
