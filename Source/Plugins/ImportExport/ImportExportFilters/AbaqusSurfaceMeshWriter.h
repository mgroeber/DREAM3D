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

#include "SIMPLib/DataArrays/DataArray.hpp"
#include "SIMPLib/Filtering/AbstractFilter.h"
#include "SIMPLib/SIMPLib.h"

#include "ImportExport/ImportExportDLLExport.h"

/**
 * @brief The AbaqusSurfaceMeshWriter class. See [Filter documentation](@ref abaqussurfacemeshwriter) for details.
 */
class ImportExport_EXPORT AbaqusSurfaceMeshWriter : public AbstractFilter
{
  Q_OBJECT

#ifdef SIMPL_ENABLE_PYTHON
  PYB11_CREATE_BINDINGS(AbaqusSurfaceMeshWriter SUPERCLASS AbstractFilter)
  PYB11_SHARED_POINTERS(AbaqusSurfaceMeshWriter)
  PYB11_FILTER_NEW_MACRO(AbaqusSurfaceMeshWriter)
  PYB11_FILTER_PARAMETER(QString, OutputFile)
  PYB11_FILTER_PARAMETER(DataArrayPath, SurfaceMeshFaceLabelsArrayPath)
  PYB11_PROPERTY(QString OutputFile READ getOutputFile WRITE setOutputFile)
  PYB11_PROPERTY(DataArrayPath SurfaceMeshFaceLabelsArrayPath READ getSurfaceMeshFaceLabelsArrayPath WRITE setSurfaceMeshFaceLabelsArrayPath)
#endif

public:
  using Self = AbaqusSurfaceMeshWriter;
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
   * @brief Returns the name of the class for AbaqusSurfaceMeshWriter
   */
  QString getNameOfClass() const override;
  /**
   * @brief Returns the name of the class for AbaqusSurfaceMeshWriter
   */
  static QString ClassName();

  ~AbaqusSurfaceMeshWriter() override;

  /**
   * @brief Setter property for OutputFile
   */
  void setOutputFile(const QString& value);
  /**
   * @brief Getter property for OutputFile
   * @return Value of OutputFile
   */
  QString getOutputFile() const;

  Q_PROPERTY(QString OutputFile READ getOutputFile WRITE setOutputFile)

  /**
   * @brief Setter property for SurfaceMeshFaceLabelsArrayPath
   */
  void setSurfaceMeshFaceLabelsArrayPath(const DataArrayPath& value);
  /**
   * @brief Getter property for SurfaceMeshFaceLabelsArrayPath
   * @return Value of SurfaceMeshFaceLabelsArrayPath
   */
  DataArrayPath getSurfaceMeshFaceLabelsArrayPath() const;

  Q_PROPERTY(DataArrayPath SurfaceMeshFaceLabelsArrayPath READ getSurfaceMeshFaceLabelsArrayPath WRITE setSurfaceMeshFaceLabelsArrayPath)

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

  /**
   * @brief preflight Reimplemented from @see AbstractFilter class
   */
  void preflight() override;

signals:
  /**
   * @brief updateFilterParameters Emitted when the Filter requests all the latest Filter parameters
   * be pushed from a user-facing control (such as a widget)
   * @param filter Filter instance pointer
   */
  void updateFilterParameters(AbstractFilter* filter);

  /**
   * @brief parametersChanged Emitted when any Filter parameter is changed internally
   */
  void parametersChanged();

  /**
   * @brief preflightAboutToExecute Emitted just before calling dataCheck()
   */
  void preflightAboutToExecute();

  /**
   * @brief preflightExecuted Emitted just after calling dataCheck()
   */
  void preflightExecuted();

protected:
  AbaqusSurfaceMeshWriter();
  /**
   * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
   */
  void dataCheck();

  /**
   * @brief Initializes all the private instance variables.
   */
  void initialize();

private:
  std::weak_ptr<DataArray<int32_t>> m_SurfaceMeshFaceLabelsPtr;
  int32_t* m_SurfaceMeshFaceLabels = nullptr;

  QString m_OutputFile = {};
  DataArrayPath m_SurfaceMeshFaceLabelsArrayPath = {};

  /**
   * @brief writeHeader Writes the header of the .inp file
   * @param f Output file
   * @param nodeCount Number of nodes
   * @param triCount Number of triangles
   * @param featureCount Number of Features
   * @return Integer error value
   */
  int32_t writeHeader(FILE* f, int64_t nodeCount, int64_t triCount, int featureCount);

  /**
   * @brief writeNodes Writes the nodes to the .inp file
   * @param f Output file
   * @return Integer error value
   */
  int32_t writeNodes(FILE* f);

  /**
   * @brief writeTriangles Writes the triangles to the .inp file
   * @param f Output file
   * @return Integer error value
   */
  int32_t writeTriangles(FILE* f);

  /**
   * @brief writeFeatures Writes the Features to the .inp file
   * @param f Output file
   * @return Integer error value
   */
  int32_t writeFeatures(FILE* f);

public:
  AbaqusSurfaceMeshWriter(const AbaqusSurfaceMeshWriter&) = delete;            // Copy Constructor Not Implemented
  AbaqusSurfaceMeshWriter(AbaqusSurfaceMeshWriter&&) = delete;                 // Move Constructor Not Implemented
  AbaqusSurfaceMeshWriter& operator=(const AbaqusSurfaceMeshWriter&) = delete; // Copy Assignment Not Implemented
  AbaqusSurfaceMeshWriter& operator=(AbaqusSurfaceMeshWriter&&) = delete;      // Move Assignment Not Implemented
};