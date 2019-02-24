#include "tp_pipeline_opencv/members/CVMatMember.h"

namespace tp_pipeline_opencv
{
//##################################################################################################
CVMatMember::CVMatMember(const std::string& name):
  tp_data::AbstractMember(name, cvMatSID())
{

}

}
