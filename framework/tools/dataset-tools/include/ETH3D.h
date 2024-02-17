/*

 Copyright (c) 2017 University of Edinburgh, Imperial College, University of
 Manchester. Developed in the PAMELA project, EPSRC Programme Grant EP/K008730/1

 This code is licensed under the MIT License.

 */

#ifndef FRAMEWORK_TOOLS_DATASET_TOOLS_INCLUDE_ETH3D_H_
#define FRAMEWORK_TOOLS_DATASET_TOOLS_INCLUDE_ETH3D_H_

#include <ParameterComponent.h>
#include <ParameterManager.h>
#include <Parameters.h>

#include <io/sensor/CameraSensor.h>
#include <io/sensor/DepthSensor.h>
#include <io/sensor/GroundTruthSensor.h>
#include <io/sensor/Sensor.h>

#include "DatasetReader.h"

namespace slambench {

    namespace io {

        class ETH3DReader : public DatasetReader {
        private:
            static constexpr image_params_t image_params =
                    { 739, 458, 27.1, 5000.0 };

            static constexpr CameraSensor::intrinsics_t intrinsics_rgb =
                    {726.28741455078, 726.28741455078, 354.6496887207, 186.46566772461};

            static constexpr DepthSensor::intrinsics_t intrinsics_depth =
                    {726.28741455078, 726.28741455078, 354.6496887207, 186.46566772461};

            static constexpr CameraSensor::distortion_coefficients_t distortion_rgb =
                    {0.0, 0.0, 0.0, 0.0, 0.0};

            static constexpr DepthSensor::distortion_coefficients_t distortion_depth =
                    {0.0, 0.0, 0.0, 0.0, 0.0};

            static constexpr DepthSensor::disparity_params_t disparity_params = {0.0002, 0.0};
            static constexpr DepthSensor::disparity_type_t disparity_type = DepthSensor::affine_disparity;
            static constexpr CameraSensor::distortion_type_t distortion_type = CameraSensor::distortion_type_t::RadialTangential;

        public:
            std::string input;
            bool grey = true, rgb = true, depth = true, gt = true, accelerometer = true;

            explicit ETH3DReader(const std::string& name) : DatasetReader(name) {
                this->addParameter(TypedParameter<std::string>("i",
                        "input-directory", "path of the TUM dataset directory",
                        &this->input, nullptr));
                this->addParameter(TypedParameter<bool>("grey", "grey",
                        "set to true or false to specify if the GREY stream need to be include in the slam file.",
                        &this->grey, nullptr));
                this->addParameter(TypedParameter<bool>("rgb", "rgb",
                        "set to true or false to specify if the RGB stream need to be include in the slam file.",
                        &this->rgb, nullptr));
                this->addParameter(TypedParameter<bool>("depth", "depth",
                        "set to true or false to specify if the DEPTH stream need to be include in the slam file.",
                        &this->depth, nullptr));
                this->addParameter(TypedParameter<bool>("gt", "gt",
                        "set to true or false to specify if the GROUNDTRUTH POSE stream need to be include in the slam file.",
                        &this->gt, nullptr));
                this->addParameter(TypedParameter<bool>("acc", "accelerometer",
                        "set to true or false to specify if the ACCELEROMETER stream need to be include in the slam file.",
                        &this->accelerometer, nullptr));
            }

            SLAMFile* GenerateSLAMFile() override;
        };
    }  // namespace io
}  // namespace slambench

#endif /* FRAMEWORK_TOOLS_DATASET_TOOLS_INCLUDE_ETH3D_H_ */