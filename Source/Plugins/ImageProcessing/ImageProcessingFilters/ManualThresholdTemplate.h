/*
 * Your License or Copyright Information can go here
 */

#ifndef _ManualThresholdTemplate_H_
#define _ManualThresholdTemplate_H_

#include <vector>
#include <QtCore/QString>

#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/DREAM3DSetGetMacros.h"
#include "DREAM3DLib/Common/AbstractFilter.h"
#include "DREAM3DLib/DataArrays/IDataArray.h"

#include "Plugins/ImageProcessing/ImageProcessingConstants.h"

#include "TemplateUtilities.h"


/**
 * @class ManualThresholdTemplate ManualThresholdTemplate.h ImageProcessing/ImageProcessingFilters/ManualThresholdTemplate.h
 * @brief
 * @author
 * @date
 * @version 1.0
 */
class ManualThresholdTemplate : public AbstractFilter
{
    Q_OBJECT /* Need this for Qt's signals and slots mechanism to work */

  public:
    DREAM3D_SHARED_POINTERS(ManualThresholdTemplate)
    DREAM3D_STATIC_NEW_MACRO(ManualThresholdTemplate)
    DREAM3D_TYPE_MACRO_SUPER(ManualThresholdTemplate, AbstractFilter)

    virtual ~ManualThresholdTemplate();

    DREAM3D_FILTER_PARAMETER(DataArrayPath, SelectedCellArrayArrayPath)
    Q_PROPERTY(DataArrayPath SelectedCellArrayArrayPath READ getSelectedCellArrayArrayPath WRITE setSelectedCellArrayArrayPath)

    DREAM3D_FILTER_PARAMETER(QString, NewCellArrayName)
    Q_PROPERTY(QString NewCellArrayName READ getNewCellArrayName WRITE setNewCellArrayName)

    DREAM3D_FILTER_PARAMETER(bool, SaveAsNewArray)
    Q_PROPERTY(bool SaveAsNewArray READ getSaveAsNewArray WRITE setSaveAsNewArray)
    DREAM3D_FILTER_PARAMETER(int, ManualParameter)
    Q_PROPERTY(int ManualParameter READ getManualParameter WRITE setManualParameter)

    /**
     * @brief getCompiledLibraryName Returns the name of the Library that this filter is a part of
     * @return
     */
    virtual const QString getCompiledLibraryName();

    /**
    * @brief This returns a string that is displayed in the GUI. It should be readable
    * and understandable by humans.
    */
    virtual const QString getHumanLabel();

    /**
    * @brief This returns the group that the filter belonds to. You can select
    * a different group if you want. The string returned here will be displayed
    * in the GUI for the filter
    */
    virtual const QString getGroupName();

    /**
    * @brief This returns a string that is displayed in the GUI and helps to sort the filters into
    * a subgroup. It should be readable and understandable by humans.
    */
    virtual const QString getSubGroupName();

    /**
    * @brief This method will instantiate all the end user settable options/parameters
    * for this filter
    */
    virtual void setupFilterParameters();

    /**
    * @brief This method will write the options to a file
    * @param writer The writer that is used to write the options to a file
    * @param index The index that the data should be written to
    * @return Returns the next index for writing
    */
    virtual int writeFilterParameters(AbstractFilterParametersWriter* writer, int index);

    /**
    * @brief This method will read the options from a file
    * @param reader The reader that is used to read the options from a file
    * @param index The index to read the information from
    */
    virtual void readFilterParameters(AbstractFilterParametersReader* reader, int index);

    /**
     * @brief Reimplemented from @see AbstractFilter class
     */
    virtual void execute();

    /**
    * @brief This function runs some sanity checks on the DataContainer and inputs
    * in an attempt to ensure the filter can process the inputs.
    */
    virtual void preflight();

    /**
     * @brief newFilterInstance Returns a new instance of the filter optionally copying the filter parameters from the
     * current filter to the new instance.
     * @param copyFilterParameters
     * @return
     */
    virtual AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters);

//virtual void ManualThresholdTemplate::template_execute();

  signals:
    /**
     * @brief updateFilterParameters This is emitted when the filter requests all the latest Filter Parameters need to be
     * pushed from a user facing control such as the FilterParameter Widget
     * @param filter The filter to push the values into
     */
    void updateFilterParameters(AbstractFilter* filter);

    /**
     * @brief parametersChanged This signal can be emitted when any of the filter parameters are changed internally.
     */
    void parametersChanged();

    /**
     * @brief preflightAboutToExecute Emitted just before the dataCheck() is called. This can change if needed.
     */
    void preflightAboutToExecute();

    /**
     * @brief preflightExecuted Emitted just after the dataCheck() is called. Typically. This can change if needed.
     */
    void preflightExecuted();

  protected:
    ManualThresholdTemplate();

    /**
    * @brief Checks for the appropriate parameter values and availability of arrays in the data container
    */
    void dataCheck();

  private:
    TEMPLATE_DEFINE_REQUIRED_DATAARRAY_VARIABLE(SelectedCellArray)
    TEMPLATE_DEFINE_CREATED_DATAARRAY_VARIABLE(NewCellArray)


    ManualThresholdTemplate(const ManualThresholdTemplate&); // Copy Constructor Not Implemented
    void operator=(const ManualThresholdTemplate&); // Operator '=' Not Implemented
};

#endif /* _ManualThresholdTemplate_H_ */