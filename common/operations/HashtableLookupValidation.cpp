/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <vector>

#include "HashtableLookup.h"
#include "OperationsUtils.h"

namespace android::nn::hashtable_lookup {

Result<Version> validate(const IOperationValidationContext* context) {
    NN_RET_CHECK(context->getNumInputs() == 3 && context->getNumOutputs() == 2)
            << context->invalidInOutNumberMessage(3, 2);
    auto inputType = context->getInputType(2);
    NN_RET_CHECK(inputType == OperandType::TENSOR_FLOAT32 ||
                 inputType == OperandType::TENSOR_INT32 ||
                 inputType == OperandType::TENSOR_QUANT8_ASYMM)
            << "Unsupported input tensor type for operation " << context->getOperationName();
    std::vector<OperandType> inExpectedTypes = {OperandType::TENSOR_INT32,
                                                OperandType::TENSOR_INT32, inputType};
    std::vector<OperandType> outExpectedTypes = {inputType, OperandType::TENSOR_QUANT8_ASYMM};
    NN_TRY(context->validateOperationOperandTypes(inExpectedTypes, outExpectedTypes));
    return kVersionFeatureLevel1;
}

}  // namespace android::nn::hashtable_lookup
