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
#include "FindLocalSlipTransmissionMetrics.h"

#include <QtCore/QTextStream>

#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/DataContainers/DataContainerArray.h"
#include "SIMPLib/FilterParameters/AbstractFilterParametersReader.h"
#include "SIMPLib/FilterParameters/DataArraySelectionFilterParameter.h"
#include "SIMPLib/FilterParameters/FloatVec3FilterParameter.h"
#include "SIMPLib/FilterParameters/LinkedPathCreationFilterParameter.h"
#include "SIMPLib/FilterParameters/SeparatorFilterParameter.h"
#include "SIMPLib/FilterParameters/StringFilterParameter.h"
#include "SIMPLib/Math/MatrixMath.h"

#include "SIMPLib/Geometry/ImageGeom.h"

#include "EbsdLib/Core/Orientation.hpp"
#include "EbsdLib/Core/OrientationTransformation.hpp"
#include "EbsdLib/Core/Quaternion.hpp"
#include "EbsdLib/LaueOps/LaueOps.h"

#include "OrientationAnalysis/OrientationAnalysisConstants.h"
#include "OrientationAnalysis/OrientationAnalysisVersion.h"

/* Create Enumerations to allow the created Attribute Arrays to take part in renaming */
enum createdPathID : RenameDataPath::DataID_t
{
  DataArrayID30 = 30,
  DataArrayID31 = 31,
  DataArrayID32 = 32,
  DataArrayID33 = 33,
  DataArrayID34 = 34,
};

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
FindLocalSlipTransmissionMetrics::FindLocalSlipTransmissionMetrics()
{
  m_LoadingDirection[0] = 1.0f;
  m_LoadingDirection[1] = 1.0f;
  m_LoadingDirection[2] = 1.0f;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
FindLocalSlipTransmissionMetrics::~FindLocalSlipTransmissionMetrics() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindLocalSlipTransmissionMetrics::setupFilterParameters()
{
  FilterParameterVectorType parameters;
  parameters.push_back(SIMPL_NEW_FLOAT_VEC3_FP("Loading Direction", LoadingDirection, FilterParameter::Category::Parameter, FindLocalSlipTransmissionMetrics));

  parameters.push_back(SeparatorFilterParameter::Create("Feature Data", FilterParameter::Category::RequiredArray));
  {
    DataArraySelectionFilterParameter::RequirementType req = DataArraySelectionFilterParameter::CreateRequirement(SIMPL::TypeNames::Float, 4, AttributeMatrix::Type::Cell, IGeometry::Type::Image);
    parameters.push_back(SIMPL_NEW_DA_SELECTION_FP("Quaternions", QuatsArrayPath, FilterParameter::Category::RequiredArray, FindLocalSlipTransmissionMetrics, req));
  }
  {
    DataArraySelectionFilterParameter::RequirementType req =
        DataArraySelectionFilterParameter::CreateRequirement(SIMPL::TypeNames::Int32, 1, AttributeMatrix::Type::Cell, IGeometry::Type::Image);
    parameters.push_back(SIMPL_NEW_DA_SELECTION_FP("Phases", PhasesArrayPath, FilterParameter::Category::RequiredArray, FindLocalSlipTransmissionMetrics, req));
  }
  parameters.push_back(SeparatorFilterParameter::Create("Ensemble Data", FilterParameter::Category::RequiredArray));
  {
    DataArraySelectionFilterParameter::RequirementType req = DataArraySelectionFilterParameter::CreateCategoryRequirement(SIMPL::TypeNames::UInt32, 1, AttributeMatrix::Category::Ensemble);
    parameters.push_back(SIMPL_NEW_DA_SELECTION_FP("Crystal Structures", CrystalStructuresArrayPath, FilterParameter::Category::RequiredArray, FindLocalSlipTransmissionMetrics, req));
  }
  parameters.push_back(SeparatorFilterParameter::Create("Feature Data", FilterParameter::Category::CreatedArray));
  parameters.push_back(SIMPL_NEW_DA_WITH_LINKED_AM_FP("F1", F1ArrayName, QuatsArrayPath, QuatsArrayPath, FilterParameter::Category::CreatedArray, FindLocalSlipTransmissionMetrics));
  parameters.push_back(SIMPL_NEW_DA_WITH_LINKED_AM_FP("F1spt", F1sptArrayName, QuatsArrayPath, QuatsArrayPath, FilterParameter::Category::CreatedArray, FindLocalSlipTransmissionMetrics));
  parameters.push_back(SIMPL_NEW_DA_WITH_LINKED_AM_FP("F7", F7ArrayName, QuatsArrayPath, QuatsArrayPath, FilterParameter::Category::CreatedArray, FindLocalSlipTransmissionMetrics));
  parameters.push_back(SIMPL_NEW_DA_WITH_LINKED_AM_FP("mPrime", mPrimeArrayName, QuatsArrayPath, QuatsArrayPath, FilterParameter::Category::CreatedArray, FindLocalSlipTransmissionMetrics));
  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindLocalSlipTransmissionMetrics::readFilterParameters(AbstractFilterParametersReader* reader, int index)
{
  reader->openFilterGroup(this, index);
  setCrystalStructuresArrayPath(reader->readDataArrayPath("CrystalStructuresArrayPath", getCrystalStructuresArrayPath()));
  setPhasesArrayPath(reader->readDataArrayPath("PhasesArrayPath", getPhasesArrayPath()));
  setQuatsArrayPath(reader->readDataArrayPath("QuatsArrayPath", getQuatsArrayPath()));
  setF1ArrayName(reader->readString("F1ArrayName", getF1ArrayName()));
  setF1sptArrayName(reader->readString("F1sptArrayName", getF1sptArrayName()));
  setF7ArrayName(reader->readString("F7ArrayName", getF7ArrayName()));
  setmPrimeArrayName(reader->readString("mPrimeArrayName", getmPrimeArrayName()));
  setLoadingDirection(reader->readFloatVec3("LoadingDirection", getLoadingDirection()));
  reader->closeFilterGroup();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindLocalSlipTransmissionMetrics::initialize()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindLocalSlipTransmissionMetrics::dataCheck()
{
  clearErrorCode();
  clearWarningCode();
  initialize();

  DataArrayPath tempPath;

  QVector<DataArrayPath> dataArrayPaths;

  std::vector<size_t> cDims(1, 4);
  m_QuatsPtr = getDataContainerArray()->getPrereqArrayFromPath<DataArray<float>>(this, getQuatsArrayPath(), cDims);
  if(nullptr != m_QuatsPtr.lock())
  {
    m_Quats = m_QuatsPtr.lock()->getPointer(0);
  } /* Now assign the raw pointer to data from the DataArray<T> object */
  if(getErrorCode() >= 0)
  {
    dataArrayPaths.push_back(getQuatsArrayPath());
  }

  cDims[0] = 1;
  m_PhasesPtr = getDataContainerArray()->getPrereqArrayFromPath<DataArray<int32_t>>(this, getPhasesArrayPath(), cDims);
  if(nullptr != m_PhasesPtr.lock())
  {
    m_Phases = m_PhasesPtr.lock()->getPointer(0);
  } /* Now assign the raw pointer to data from the DataArray<T> object */
  if(getErrorCode() >= 0)
  {
    dataArrayPaths.push_back(getPhasesArrayPath());
  }

  m_CrystalStructuresPtr = getDataContainerArray()->getPrereqArrayFromPath<DataArray<uint32_t>>(this, getCrystalStructuresArrayPath(), cDims);
  if(nullptr != m_CrystalStructuresPtr.lock())
  {
    m_CrystalStructures = m_CrystalStructuresPtr.lock()->getPointer(0);
  } /* Now assign the raw pointer to data from the DataArray<T> object */


  tempPath.update(m_PhasesArrayPath.getDataContainerName(), m_PhasesArrayPath.getAttributeMatrixName(), getF1ArrayName());
  m_F1Ptr = getDataContainerArray()->createNonPrereqArrayFromPath<DataArray<float>>(this, tempPath, 0, cDims, "", DataArrayID31);
  if(nullptr != m_F1Ptr.lock())
  {
    m_F1 = m_F1Ptr.lock()->getPointer(0);
  } /* Now assign the raw pointer to data from the DataArray<T> object */

  tempPath.update(m_PhasesArrayPath.getDataContainerName(), m_PhasesArrayPath.getAttributeMatrixName(), getF1sptArrayName());
  m_F1sptPtr = getDataContainerArray()->createNonPrereqArrayFromPath<DataArray<float>>(this, tempPath, 0, cDims, "", DataArrayID32);
  if(nullptr != m_F1sptPtr.lock())
  {
    m_F1spt = m_F1sptPtr.lock()->getPointer(0);
  } /* Now assign the raw pointer to data from the DataArray<T> object */

  tempPath.update(m_PhasesArrayPath.getDataContainerName(), m_PhasesArrayPath.getAttributeMatrixName(), getF7ArrayName());
  m_F7Ptr = getDataContainerArray()->createNonPrereqArrayFromPath<DataArray<float>>(this, tempPath, 0, cDims, "", DataArrayID33);
  if(nullptr != m_F7Ptr.lock())
  {
    m_F7 = m_F7Ptr.lock()->getPointer(0);
  } /* Now assign the raw pointer to data from the DataArray<T> object */

  tempPath.update(m_PhasesArrayPath.getDataContainerName(), m_PhasesArrayPath.getAttributeMatrixName(), getmPrimeArrayName());
  m_mPrimePtr = getDataContainerArray()->createNonPrereqArrayFromPath<DataArray<float>>(this, tempPath, 0, cDims, "", DataArrayID34);
  if(nullptr != m_mPrimePtr.lock())
  {
    m_mPrime = m_mPrimePtr.lock()->getPointer(0);
  } /* Now assign the raw pointer to data from the DataArray<T> object */
  
  getDataContainerArray()->validateNumberOfTuples(this, dataArrayPaths);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindLocalSlipTransmissionMetrics::execute()
{
  dataCheck();
  if(getErrorCode() < 0)
  {
    return;
  }
  std::vector<LaueOps::Pointer> m_OrientationOps = LaueOps::GetAllOrientationOps();

  size_t totalElements = m_PhasesPtr.lock()->getNumberOfTuples();

  double mPrime = 0.0, F1 = 0.0, F1spt = 0.0, F7 = 0.0;

  FloatArrayType::Pointer quatPtr = m_QuatsPtr.lock();

  double LD[3] = {0.0f, 0.0f, 1.0f};

  LD[0] = m_LoadingDirection[0];
  LD[1] = m_LoadingDirection[1];
  LD[2] = m_LoadingDirection[2];
  MatrixMath::Normalize3x1(LD);

  DataContainer::Pointer m = getDataContainerArray()->getDataContainer(m_QuatsArrayPath.getDataContainerName());
  SizeVec3Type udims = m->getGeometryAs<ImageGeom>()->getDimensions();

  int64_t dims[3] = {
      static_cast<int64_t>(udims[0]),
      static_cast<int64_t>(udims[1]),
      static_cast<int64_t>(udims[2]),
  };

  int64_t neighpoints[6] = {0, 0, 0, 0, 0, 0};
  neighpoints[0] = -dims[0] * dims[1];
  neighpoints[1] = -dims[0];
  neighpoints[2] = -1;
  neighpoints[3] = 1;
  neighpoints[4] = dims[0];
  neighpoints[5] = dims[0] * dims[1];

  int32_t progFeature = 0;
  int32_t progFeatureInc = static_cast<int32_t>(totalElements * 0.01f);

  int64_t column = 0, row = 0, plane = 0;
  int64_t neighpoint = 0;
  int32_t good = 1;
  int64_t neighbor;
  float maxF1 = 0.0;
  float maxF1spt = 0.0;
  float maxF7 = 0.0;
  float minmPrime = 1.0;
  for(size_t i = 0; i < totalElements; i++)
  {
    maxF1 = 0.0f;
    maxF1spt = 0.0f;
    maxF7 = 0.0f;
    minmPrime = 1.0f;

    if(getCancel())
    {
      return;
    }
    if(static_cast<int32_t>(i) > progFeature + progFeatureInc)
    {
      QString ss = QObject::tr("Finding Local Slip Transmission Metrics - %1%").arg(100.0f * float(i)/float(totalElements));
      notifyStatusMessage(ss);
      progFeature = i;
    }

    column = i % dims[0];
    row = (i / dims[0]) % dims[1];
    plane = i / (dims[0] * dims[1]);
    for(int32_t j = 0; j < 6; j++)
    {
      good = 1;
      neighbor = i + neighpoints[j];
      if(j == 0 && plane == 0)
      {
        good = 0;
      }
      if(j == 5 && plane == (dims[2] - 1))
      {
        good = 0;
      }
      if(j == 1 && row == 0)
      {
        good = 0;
      }
      if(j == 4 && row == (dims[1] - 1))
      {
        good = 0;
      }
      if(j == 2 && column == 0)
      {
        good = 0;
      }
      if(j == 3 && column == (dims[0] - 1))
      {
        good = 0;
      }
      if(good == 1)
      {
        QuatD q1(m_Quats[4 * i], m_Quats[4 * i + 1], m_Quats[4 * i + 2], m_Quats[4 * i + 3]);
        QuatD q2(m_Quats[4 * neighbor], m_Quats[4 * neighbor + 1], m_Quats[4 * neighbor + 2], m_Quats[4 * neighbor + 3]);

        if(m_CrystalStructures[m_Phases[i]] == m_CrystalStructures[m_Phases[neighbor]] && m_Phases[i] > 0)
        {
          mPrime = m_OrientationOps[m_CrystalStructures[m_Phases[i]]]->getmPrime(q1, q2, LD);
          F1 = m_OrientationOps[m_CrystalStructures[m_Phases[i]]]->getF1(q1, q2, LD, true);
          F1spt = m_OrientationOps[m_CrystalStructures[m_Phases[i]]]->getF1spt(q1, q2, LD, true);
          F7 = m_OrientationOps[m_CrystalStructures[m_Phases[i]]]->getF7(q1, q2, LD, true);
          if(F1 > maxF1)
          {
            maxF1 = F1;
          }
          if(F1spt > maxF1spt)
          {
            maxF1spt = F1spt;
          }
          if(F7 > maxF7)
          {
            maxF7 = F7;
          }
          if(mPrime < minmPrime)
          {
            minmPrime = mPrime;
          }
        }
      }
    }
    m_mPrime[i] = minmPrime;
    m_F1[i] = maxF1;
    m_F1spt[i] = maxF1spt;
    m_F7[i] = maxF7;
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AbstractFilter::Pointer FindLocalSlipTransmissionMetrics::newFilterInstance(bool copyFilterParameters) const
{
  FindLocalSlipTransmissionMetrics::Pointer filter = FindLocalSlipTransmissionMetrics::New();
  if(copyFilterParameters)
  {
    copyFilterParameterInstanceVariables(filter.get());
  }
  return filter;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString FindLocalSlipTransmissionMetrics::getCompiledLibraryName() const
{
  return OrientationAnalysisConstants::OrientationAnalysisBaseName;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString FindLocalSlipTransmissionMetrics::getBrandingString() const
{
  return "OrientationAnalysis";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString FindLocalSlipTransmissionMetrics::getFilterVersion() const
{
  QString version;
  QTextStream vStream(&version);
  vStream << OrientationAnalysis::Version::Major() << "." << OrientationAnalysis::Version::Minor() << "." << OrientationAnalysis::Version::Patch();
  return version;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString FindLocalSlipTransmissionMetrics::getGroupName() const
{
  return SIMPL::FilterGroups::StatisticsFilters;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QUuid FindLocalSlipTransmissionMetrics::getUuid() const
{
  return QUuid("{97523038-5fb2-5e82-9177-ed3e8b24b4df}");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString FindLocalSlipTransmissionMetrics::getSubGroupName() const
{
  return SIMPL::FilterSubGroups::CrystallographyFilters;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString FindLocalSlipTransmissionMetrics::getHumanLabel() const
{
  return "Find Local Slip Transmission Metrics";
}

// -----------------------------------------------------------------------------
FindLocalSlipTransmissionMetrics::Pointer FindLocalSlipTransmissionMetrics::NullPointer()
{
  return Pointer(static_cast<Self*>(nullptr));
}

// -----------------------------------------------------------------------------
std::shared_ptr<FindLocalSlipTransmissionMetrics> FindLocalSlipTransmissionMetrics::New()
{
  struct make_shared_enabler : public FindLocalSlipTransmissionMetrics
  {
  };
  std::shared_ptr<make_shared_enabler> val = std::make_shared<make_shared_enabler>();
  val->setupFilterParameters();
  return val;
}

// -----------------------------------------------------------------------------
QString FindLocalSlipTransmissionMetrics::getNameOfClass() const
{
  return QString("FindLocalSlipTransmissionMetrics");
}

// -----------------------------------------------------------------------------
QString FindLocalSlipTransmissionMetrics::ClassName()
{
  return QString("FindLocalSlipTransmissionMetrics");
}

// -----------------------------------------------------------------------------
void FindLocalSlipTransmissionMetrics::setF1ArrayName(const QString& value)
{
  m_F1ArrayName = value;
}

// -----------------------------------------------------------------------------
QString FindLocalSlipTransmissionMetrics::getF1ArrayName() const
{
  return m_F1ArrayName;
}

// -----------------------------------------------------------------------------
void FindLocalSlipTransmissionMetrics::setF1sptArrayName(const QString& value)
{
  m_F1sptArrayName = value;
}

// -----------------------------------------------------------------------------
QString FindLocalSlipTransmissionMetrics::getF1sptArrayName() const
{
  return m_F1sptArrayName;
}

// -----------------------------------------------------------------------------
void FindLocalSlipTransmissionMetrics::setF7ArrayName(const QString& value)
{
  m_F7ArrayName = value;
}

// -----------------------------------------------------------------------------
QString FindLocalSlipTransmissionMetrics::getF7ArrayName() const
{
  return m_F7ArrayName;
}

// -----------------------------------------------------------------------------
void FindLocalSlipTransmissionMetrics::setmPrimeArrayName(const QString& value)
{
  m_mPrimeArrayName = value;
}

// -----------------------------------------------------------------------------
QString FindLocalSlipTransmissionMetrics::getmPrimeArrayName() const
{
  return m_mPrimeArrayName;
}

// -----------------------------------------------------------------------------
void FindLocalSlipTransmissionMetrics::setQuatsArrayPath(const DataArrayPath& value)
{
  m_QuatsArrayPath = value;
}

// -----------------------------------------------------------------------------
DataArrayPath FindLocalSlipTransmissionMetrics::getQuatsArrayPath() const
{
  return m_QuatsArrayPath;
}

// -----------------------------------------------------------------------------
void FindLocalSlipTransmissionMetrics::setPhasesArrayPath(const DataArrayPath& value)
{
  m_PhasesArrayPath = value;
}

// -----------------------------------------------------------------------------
DataArrayPath FindLocalSlipTransmissionMetrics::getPhasesArrayPath() const
{
  return m_PhasesArrayPath;
}

// -----------------------------------------------------------------------------
void FindLocalSlipTransmissionMetrics::setCrystalStructuresArrayPath(const DataArrayPath& value)
{
  m_CrystalStructuresArrayPath = value;
}

// -----------------------------------------------------------------------------
DataArrayPath FindLocalSlipTransmissionMetrics::getCrystalStructuresArrayPath() const
{
  return m_CrystalStructuresArrayPath;
}

// -----------------------------------------------------------------------------
void FindLocalSlipTransmissionMetrics::setLoadingDirection(const FloatVec3Type& value)
{
  m_LoadingDirection = value;
}

// -----------------------------------------------------------------------------
FloatVec3Type FindLocalSlipTransmissionMetrics::getLoadingDirection() const
{
  return m_LoadingDirection;
}