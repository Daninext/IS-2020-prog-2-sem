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

const int TABLE_SIZE = 10000;

vector<std::u16string> names;
vector<std::u16string> vehTypes;
vector<int> namesValue;
map<std::u16string, vector<Route>> allRoutes;

std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> utf16conv;
std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter;

int hashCode(std::string name)
{
    return abs((int)std::hash<std::string>()(name)) % TABLE_SIZE;
}

int u16hashCode(std::u16string name)
{
    return abs((int)std::hash<std::u16string>()(name)) % TABLE_SIZE;
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("data.xml");
    if (!result)
        return -1;

    names.resize(TABLE_SIZE);
    namesValue.resize(TABLE_SIZE);

    for (pugi::xml_node station : doc.child("dataset").children("transport_station"))
    {
        std::string s_routes = station.child("routes").text().as_string();
        boost::replace_all(s_routes, ",", " ");
        boost::replace_all(s_routes, ".", " ");
        vector<std::string> vs_routes;
        boost::split(vs_routes, s_routes, boost::is_any_of(" "));
        
        std::string s_coords = station.child("coordinates").text().as_string();
        boost::replace_all(s_coords, ",", " ");
        stringstream sst(s_coords);
        float x, y;
        sst >> x; sst >> y;

        std::string u8name = station.child("type_of_vehicle").text().as_string();
        std::u16string u16name = utf16conv.from_bytes(u8name);

        if (allRoutes.count(u16name) == 0) {
            allRoutes[u16name].resize(TABLE_SIZE);
            vehTypes.push_back(u16name);
        } 

        for (int i = 0; i != vs_routes.size(); i++) {
            int hash = hashCode(vs_routes[i]);

            if (allRoutes[u16name][hash].name() == "none")
                allRoutes[u16name][hash].SetName(vs_routes[i]);

            allRoutes[u16name][hash].ItValue();
            allRoutes[u16name][hash].AddCoord(x, y);
        }

        std::string s_loc = station.child("location").text().as_string();
        std::u16string u16_loc = utf16conv.from_bytes(s_loc);
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

        vector<std::u16string> vu16_loc;
        boost::split(vu16_loc, u16_loc, boost::is_any_of(","));

        for (int i = 0; i != vu16_loc.size(); i++) {
            int hash = u16hashCode(vu16_loc[i]);

            if (names[hash].size() == 0)
                names[hash] = vu16_loc[i];

            namesValue[hash]++;
        }
    }

    for (int i = 0; i != vehTypes.size(); i++) {
        string maxRouteName;
        int maxRouteValue = 0;
        for (int j = 0; j != TABLE_SIZE; j++) {
            if (allRoutes[vehTypes[i]][j].name() != "none") {
                if (allRoutes[vehTypes[i]][j].value() > maxRouteValue) {
                    maxRouteValue = allRoutes[vehTypes[i]][j].value();
                    maxRouteName = allRoutes[vehTypes[i]][j].name();
                }
            }
        }

        cout << "Max Route - \"" << maxRouteName << "\" = " << maxRouteValue << " (" << converter.to_bytes(vehTypes[i]) << ")\n";
    }

    cout << endl;

    for (int i = 0; i != vehTypes.size(); i++) {
        string maxRouteName;
        float maxRouteDistance = 0;
        for (int j = 0; j != TABLE_SIZE; j++) {
            if (allRoutes[vehTypes[i]][j].name() != "none") {
                float dist = allRoutes[vehTypes[i]][j].GetSize();
                if (dist > maxRouteDistance) {
                    maxRouteDistance = dist;
                    maxRouteName = allRoutes[vehTypes[i]][j].name();
                }
            }
        }

        cout << "Max distance Route - \"" << maxRouteName << "\" (" << converter.to_bytes(vehTypes[i]) << ")\n";
    }

    cout << endl;

    int maxValue = 0;
    u16string maxName;
    for (int i = 0; i != TABLE_SIZE; i++) {
        if (names[i].size() != 0) {
            if (namesValue[i] > maxValue) {
                maxValue = namesValue[i];
                maxName = names[i];
            }
        }
    }

    cout << "Street with max stops - " << converter.to_bytes(maxName) << " = " << maxValue << endl;

    return 0;
}