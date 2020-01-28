#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include <string>
#include <vector>

#include "MNN/Interpreter.hpp"
#include "MNN/ImageProcess.hpp"
#include "MNN/MNNDefine.h"
#include "MNN/Tensor.hpp"

#include "opencv2/core.hpp"

namespace mirror {

struct ImageInfo {
    std::string label_;
    float score_;
};

class Classifier {
public:
    Classifier();
    ~Classifier();
    int Init(const char* root_path);
    int Classify(const cv::Mat& img_src, std::vector<ImageInfo>* images);

private:
    bool initialized_;
    std::shared_ptr<MNN::Interpreter> mobilenet_interpreter_;
    MNN::Session* mobilenet_sess_ = nullptr;
    MNN::Tensor* input_tensor_ = nullptr;

    const cv::Size inputSize_ = cv::Size(224, 224);
    const float meanVals[3] = { 103.94f, 116.78f, 123.68f };
    const float normVals[3] = {  0.017f,  0.017f,  0.017f };

    std::vector<std::string> labels_;
    int topk_;

    int LoadLabels(const char* root_path);

};

}



#endif  // !_CLASSIFIER_H_