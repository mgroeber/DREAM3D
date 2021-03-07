/* ============================================================================
 * Copyright (c) 2009-2016 BlueQuartz Software, LLC
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
 * contributors may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The code contained herein was partially funded by the followig contracts:
 *    United States Air Force Prime Contract FA8650-07-D-5800
 *    United States Air Force Prime Contract FA8650-10-D-5210
 *    United States Prime Contract Navy N00173-07-C-2068
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#pragma once

#include <memory>

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/DataArrays/DataArray.hpp"
#include "SIMPLib/DataArrays/NeighborList.hpp"
#include "SIMPLib/Filtering/AbstractFilter.h"

#include "OrientationAnalysis/OrientationAnalysisDLLExport.h"

class LaueOps;
using LaueOpsShPtrType = std::shared_ptr<LaueOps>;
using LaueOpsContainer = std::vector<LaueOpsShPtrType>;

/**
 * @brief The FindLocalSlipTransmissionMetrics class. See [Filter documentation](@ref FindLocalSliptransmissionmetrics) for details.
 */
class OrientationAnalysis_EXPORT FindLocalSlipTransmissionMetrics : public AbstractFilter
{
  Q_OBJECT

  // Start Python bindings declarations
  PYB11_BEGIN_BINDINGS(FindLocalSlipTransmissionMetrics SUPERCLASS AbstractFilter)
  PYB11_FILTER()
  PYB11_SHARED_POINTERS(FindLocalSlipTransmissionMetrics)
  PYB11_FILTER_NEW_MACRO(FindLocalSlipTransmissionMetrics)
  PYB11_PROPERTY(QString F1ListArrayName READ getF1ListArrayName WRITE setF1ListArrayName)
  PYB11_PROPERTY(QString F1sptListArrayName READ getF1sptListArrayName WRITE setF1sptListArrayName)
  PYB11_PROPERTY(QString F7ListArrayName READ getF7ListArrayName WRITE setF7ListArrayName)
  PYB11_PROPERTY(QString mPrimeListArrayName READ getmPrimeListArrayName WRITE setmPrimeListArrayName)
  PYB11_PROPERTY(DataArrayPath QuatsArrayPath READ getQuatsArrayPath WRITE setQuatsArrayPath)
  PYB11_PROPERTY(DataArrayPath PhasesArrayPath READ getPhasesArrayPath WRITE setPhasesArrayPath)
  PYB11_PROPERTY(DataArrayPath CrystalStructuresArrayPath READ getCrystalStructuresArrayPath WRITE setCrystalStructuresArrayPath)
  PYB11_END_BINDINGS()
  // End Python bindings declarations

public:
  using Self = FindLocalSlipTransmissionMetrics;
  using Pointer = std::shared_ptr<Self>;
  using ConstPointer = std::shared_ptr<const Self>;
  using WeakPointer = std::weak_ptr<Self>;
  using ConstWeakPointer = std::weak_ptr<const Self>;

  /**
   * @brief Returns a NullPointer wrapped by a shared_ptr<>
   * @return
   */
  static Pointer NullPointer();

  /**
   * @brief Creates a new object wrapped in a shared_ptr<>
   * @return
   */
  static Pointer New();

  /**
   * @brief Returns the name of the class for FindLocalSlipTransmissionMetrics
   */
  QString getNameOfClass() const override;
  /**
   * @brief Returns the name of the class for FindLocalSlipTransmissionMetrics
   */
  static QString ClassName();

  ~FindLocalSlipTransmissionMetrics() override;


  /**
   * @brief Setter property for F1ListArrayName
   */
  void setF1ArrayName(const QString& value);
  /**
   * @brief Getter property for F1ListArrayName
   * @return Value of F1ListArrayName
   */
  QString getF1ArrayName() const;
  Q_PROPERTY(QString F1ArrayName READ getF1ArrayName WRITE setF1ArrayName)

  /**
   * @brief Setter property for F1sptListArrayName
   */
  void setF1sptArrayName(const QString& value);
  /**
   * @brief Getter property for F1sptListArrayName
   * @return Value of F1sptListArrayName
   */
  QString getF1sptArrayName() const;
  Q_PROPERTY(QString F1sptArrayName READ getF1sptArrayName WRITE setF1sptArrayName)

  /**
   * @brief Setter property for F7ListArrayName
   */
  void setF7ArrayName(const QString& value);
  /**
   * @brief Getter property for F7ListArrayName
   * @return Value of F7ListArrayName
   */
  QString getF7ArrayName() const;
  Q_PROPERTY(QString F7ArrayName READ getF7ArrayName WRITE setF7ArrayName)

  /**
   * @brief Setter property for mPrimeListArrayName
   */
  void setmPrimeArrayName(const QString& value);
  /**
   * @brief Getter property for mPrimeListArrayName
   * @return Value of mPrimeListArrayName
   */
  QString getmPrimeArrayName() const;
  Q_PROPERTY(QString mPrimeArrayName READ getmPrimeArrayName WRITE setmPrimeArrayName)

  /**
   * @brief Setter property for QuatsArrayPath
   */
  void setQuatsArrayPath(const DataArrayPath& value);
  /**
   * @brief Getter property for QuatsArrayPath
   * @return Value of QuatsArrayPath
   */
  DataArrayPath getQuatsArrayPath() const;
  Q_PROPERTY(DataArrayPath QuatsArrayPath READ getQuatsArrayPath WRITE setQuatsArrayPath)

  /**
   * @brief Setter property for PhasesArrayPath
   */
  void setPhasesArrayPath(const DataArrayPath& value);
  /**
   * @brief Getter property for PhasesArrayPath
   * @return Value of PhasesArrayPath
   */
  DataArrayPath getPhasesArrayPath() const;
  Q_PROPERTY(DataArrayPath PhasesArrayPath READ getPhasesArrayPath WRITE setPhasesArrayPath)

  /**
   * @brief Setter property for CrystalStructuresArrayPath
   */
  void setCrystalStructuresArrayPath(const DataArrayPath& value);
  /**
   * @brief Getter property for CrystalStructuresArrayPath
   * @return Value of CrystalStructuresArrayPath
   */
  DataArrayPath getCrystalStructuresArrayPath() const;
  Q_PROPERTY(DataArrayPath CrystalStructuresArrayPath READ getCrystalStructuresArrayPath WRITE setCrystalStructuresArrayPath)

  /**
   * @brief getCompiledLibraryName Reimplemented from @see AbstractFilter class
   */
  QString getCompiledLibraryName() const override;

  /**
   * @brief getBrandingString Returns the branding string for the filter, which is a tag
   * used to denote the filter's association with specific plugins
   * @return Branding string
   */
  QString getBrandingString() const override;

  /**
   * @brief getFilterVersion Returns a version string for this filter. Default
   * value is an empty string.
   * @return
   */
  QString getFilterVersion() const override;

  /**
   * @brief newFilterInstance Reimplemented from @see AbstractFilter class
   */
  AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters) const override;

  /**
   * @brief getGroupName Reimplemented from @see AbstractFilter class
   */
  QString getGroupName() const override;

  /**
   * @brief getSubGroupName Reimplemented from @see AbstractFilter class
   */
  QString getSubGroupName() const override;

  /**
   * @brief getUuid Return the unique identifier for this filter.
   * @return A QUuid object.
   */
  QUuid getUuid() const override;

  /**
   * @brief getHumanLabel Reimplemented from @see AbstractFilter class
   */
  QString getHumanLabel() const override;

  /**
   * @brief setupFilterParameters Reimplemented from @see AbstractFilter class
   */
  void setupFilterParameters() override;

  /**
   * @brief readFilterParameters Reimplemented from @see AbstractFilter class
   */
  void readFilterParameters(AbstractFilterParametersReader* reader, int index) override;

  /**
   * @brief execute Reimplemented from @see AbstractFilter class
   */
  void execute() override;

protected:
  FindLocalSlipTransmissionMetrics();
  /**
   * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
   */
  void dataCheck() override;

  /**
   * @brief Initializes all the private instance variables.
   */
  void initialize();

private:
  std::weak_ptr<DataArray<int32_t>> m_PhasesPtr;
  int32_t* m_Phases = nullptr;
  std::weak_ptr<DataArray<float>> m_QuatsPtr;
  float* m_Quats = nullptr;
  std::weak_ptr<DataArray<uint32_t>> m_CrystalStructuresPtr;
  uint32_t* m_CrystalStructures = nullptr;
  std::weak_ptr<DataArray<float>> m_F1Ptr;
  float* m_F1 = nullptr;
  std::weak_ptr<DataArray<float>> m_F1sptPtr;
  float* m_F1spt = nullptr;
  std::weak_ptr<DataArray<float>> m_F7Ptr;
  float* m_F7 = nullptr;
  std::weak_ptr<DataArray<float>> m_mPrimePtr;
  float* m_mPrime = nullptr;

  QString m_F1ArrayName = {""};
  QString m_F1sptArrayName = {""};
  QString m_F7ArrayName = {""};
  QString m_mPrimeArrayName = {""};
  DataArrayPath m_QuatsArrayPath = {"", "", ""};
  DataArrayPath m_PhasesArrayPath = {"", "", ""};
  DataArrayPath m_CrystalStructuresArrayPath = {"", "", ""};

  LaueOpsContainer m_OrientationOps;

public:
  FindLocalSlipTransmissionMetrics(const FindLocalSlipTransmissionMetrics&) = delete;            // Copy Constructor Not Implemented
  FindLocalSlipTransmissionMetrics(FindLocalSlipTransmissionMetrics&&) = delete;                 // Move Constructor Not Implemented
  FindLocalSlipTransmissionMetrics& operator=(const FindLocalSlipTransmissionMetrics&) = delete; // Copy Assignment Not Implemented
  FindLocalSlipTransmissionMetrics& operator=(FindLocalSlipTransmissionMetrics&&) = delete;      // Move Assignment Not Implemented
};
