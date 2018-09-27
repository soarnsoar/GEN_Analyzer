cp DY_preFSR_analyzer_boson_added_muon.cc DY_preFSR_analyzer_boson_added_electron.cc
find . -name DY_preFSR_analyzer_boson_added_electron.cc | xargs perl -pi -e s/"int leppid=13"/"int leppid=11"/g
find . -name DY_preFSR_analyzer_boson_added_electron.cc | xargs perl -pi -e s/"DY_preFSR_analyzer_boson_added_muon"/"DY_preFSR_analyzer_boson_added_electron"/g

#int leppid=11