#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <locale>
#include <codecvt>
#include <windows.h>
#include <math.h>
#include "pugixml.hpp"
#include "stoper.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

//todo first second
map<u16string, int> namesScore;
vector<u16string> vehTypes;
map<u16string, map<string, Route>> allRoutes;

wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> utf16conv;
wstring_convert<codecvt_utf8<char16_t>, char16_t> converter;

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("data.xml");
    if (!result)
        return -1;

    for (pugi::xml_node station : doc.child("dataset").children("transport_station"))
    {
        string s_routes = station.child("routes").text().as_string();
        boost::replace_all(s_routes, ",", " ");
        boost::replace_all(s_routes, ".", " ");
        vector<string> vs_routes;
        boost::split(vs_routes, s_routes, boost::is_any_of(" "));
        
        string s_coords = station.child("coordinates").text().as_string();
        boost::replace_all(s_coords, ",", " ");
        stringstream sst(s_coords);
        float x, y;
        sst >> x; sst >> y;

        string u8name = station.child("type_of_vehicle").text().as_string();
        u16string u16name = utf16conv.from_bytes(u8name);

        if (allRoutes.count(u16name) == 0) {
            vehTypes.push_back(u16name);
        } 

        for (int i = 0; i != vs_routes.size(); i++) {
            if (vs_routes[i] != " " && vs_routes[i] != "")
                if (allRoutes[u16name].count(vs_routes[i]) == 0) {
                    Route r;
                    r.SetName(vs_routes[i]);
                    r.ItValue();
                    r.AddCoord(x, y);

                    allRoutes[u16name].insert(make_pair(vs_routes[i], r));
                }
                else {
                    allRoutes[u16name][vs_routes[i]].ItValue();
                    allRoutes[u16name][vs_routes[i]].AddCoord(x, y);
                }
        }

        string s_loc = station.child("location").text().as_string();
        u16string u16_loc = utf16conv.from_bytes(s_loc);
        boost::replace_all(u16_loc, L"ул.", "");
        boost::replace_all(u16_loc, L"пр.", "");
        boost::replace_all(u16_loc, L"пл.", "");
        boost::replace_all(u16_loc, L"площадь", "");
        boost::replace_all(u16_loc, L"ш.", "");
        boost::replace_all(u16_loc, L"улица", "");
        boost::replace_all(u16_loc, L"проспект", "");
        boost::replace_all(u16_loc, L"шоссе", "");
        boost::replace_all(u16_loc, L"проспект", "");
        boost::replace_all(u16_loc, L"переулок", "");
        boost::replace_all(u16_loc, L"мост", "");
        boost::replace_all(u16_loc, L"аллея", "");
        boost::replace_all(u16_loc, L"проезд", "");
        boost::replace_all(u16_loc, " ", "");

        vector<u16string> vu16_loc;
        boost::split(vu16_loc, u16_loc, boost::is_any_of(","));

        for (int i = 0; i != vu16_loc.size(); i++) {
            if (vu16_loc[i].size() != 0)
                if (namesScore.count(vu16_loc[i]) == 0) {
                    namesScore.insert(make_pair(vu16_loc[i], 1));
                }
                else {
                    namesScore[vu16_loc[i]]++;
                }
        }
    }

    for (int i = 0; i != vehTypes.size(); i++) {
        string maxRouteName;
        int maxRouteValue = 0;
        for (auto& t : allRoutes[vehTypes[i]]) {
            if (t.second.value() > maxRouteValue) {
                maxRouteValue = t.second.value();
                maxRouteName = t.second.name();
            }
        }

        cout << "Max Route - \"" << maxRouteName << "\" = " << maxRouteValue << " (" << converter.to_bytes(vehTypes[i]) << ")\n";
    }

    cout << endl;

    for (int i = 0; i != vehTypes.size(); i++) {
        string maxRouteName;
        float maxRouteDistance = 0;
        for (auto& t : allRoutes[vehTypes[i]]) {
            float dist = t.second.GetSize();
            if (dist > maxRouteDistance) {
                maxRouteDistance = dist;
                maxRouteName = t.second.name();
            }
        }

        cout << "Max distance Route - \"" << maxRouteName << "\" (" << converter.to_bytes(vehTypes[i]) << ")\n";
    }

    cout << endl;

    int maxValue = 0;
    u16string maxName;
    for (auto& t : namesScore) {
        if (t.second > maxValue) {
            maxValue = t.second;
            maxName = t.first;
        }
    }

    cout << "Street with max stops - " << converter.to_bytes(maxName) << " = " << maxValue << endl;

    return 0;
}