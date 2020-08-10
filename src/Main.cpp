#include "Edge.h"
#include "Node.h"
#include "Graaf.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<queue>
#include<memory>
#include<unordered_map>
#include<stack>

using namespace std;


// Reads file to graph
// Returns true if reading was successful, false otherwise
bool readCSVToGraph(string failinimi, Graph& G)
{
    vector<string> row;
    string line, word;
    ifstream myfile(failinimi);
    if (myfile.is_open())
    {

        // Esimene rida - tipud
        if (getline(myfile, line)) {
            stringstream s(line);
            while (getline(s, word, ',')) {
                // add all the column data of a row to a vector 
                shared_ptr<Node> np = make_shared<Node>(word);
                G.node_map[word] = np;
                G.nodes.push_back(np);
            }
        }

        // �lej��nud read - kaared
        while (getline(myfile, line))
        {
            row.clear();
            // skips empty lines
            if (line.empty())
            {
                continue;
            }
            stringstream s(line);

            while (getline(s, word, ',')) {
                row.push_back(word);
            }

            if (row.size() == 3) {
                try
                {
                    if (G.node_map.find(row[0]) == G.node_map.end()) {
                        cout << "tipp '" << row[0] << "' ei ole defineeritud" << endl;
                        throw invalid_argument("");
                    }
                    if (G.node_map.find(row[1]) == G.node_map.end()) {
                        cout << "Tipp '" << row[1] << "' ei ole defineeritud" << endl;
                        throw invalid_argument("");
                    }
                    shared_ptr<Node> np1 = G.node_map[row[0]];
                    shared_ptr<Node> np2 = G.node_map[row[1]];
                    double w = stod(row[2]);
                    if (w<0)
                    {
                        cout << "Graaf ei tohi sisaldada negatiivse kaaluga servi." << endl;
                        cout << "Sellisel juhul ei pruugi Djikstra algoritm anda oigeid kaugusi." << endl;
                        return false;
                    }
                    shared_ptr<Edge> ep = make_shared<Edge>(np1, np2, w);

                    G.edges[np1->m_name].push_back(ep);

                }
                catch (const std::exception&)
                {
                    cout << "Viga graafi failis real: " << line << endl;
                    return false;
                }

            }
            else {
                cout << "Ootasin kolme kaare argumenti(string tipp1_nimi, string tipp2_nimi, double kaal) real: " << line << endl;
                return false;
            }

        }
        myfile.close();
        return true;
    }

    else {
        cout << "Ei leidnud faili nimega: " << failinimi << endl;
        return false;
    } 

}

bool graphInactive(Graph& G) {
    if (!G.active)
    {
        cout << "Graaf ei ole veel sisse loetud." << endl;
        return true;
    }
    return false;
}

void handleDisplayingGraphInfo(Graph& G) {
    if (graphInactive(G)) return;

    cout << "Registreeritud graaf:" << endl;
    cout << "Tipud: ";
    bool esimene = true;

    auto itNodes = G.nodes.begin();
    while (itNodes!=G.nodes.end())
    {
        if (esimene)
        {
            cout << **itNodes;
            esimene = false;
        }
        else {
            cout << ", " << **itNodes;
        }
        itNodes++;
    }
    cout << endl;
    
    esimene = true;
    cout << "Kaared: ";
    auto itEdges = G.edges.begin();
    while (itEdges != G.edges.end())
    {
        vector<shared_ptr<Edge>> v = (*itEdges).second;
        for (shared_ptr<Edge> e : v) {
            if (esimene)
            {
                cout << *e;
                esimene = false;
            }
            else {
                cout << ", " << *e;
            }
        }
        
        itEdges++;
    }
    cout << endl;
}

void clearGraph(Graph& G)
{
    G.nodes.clear();
    G.node_map.clear();
    G.edges.clear();
}

void handleGraphReading(Graph& G, bool autoread = false) {
    string failinimi;
    clearGraph(G);

    if (autoread)
    {
        failinimi = "graaf.csv";
    }
    else {
        cout << "Sisesta failinimi (default 'graaf.csv'): ";

        getline(cin, failinimi);

        if (failinimi.empty())
        {
            failinimi = "graaf.csv";
        }
    }


    bool success = readCSVToGraph(failinimi, G);
    
    if (success) {
        G.active = true;
        handleDisplayingGraphInfo(G);
    }
    else{
        cout << endl;
        cout << "Graafi lugemine ebaonnestus." << endl;
        G.active = false;
        clearGraph(G);
    }
}

void handleDistanceMeasurement(Graph& G) {
    if (graphInactive(G)) return;

    if (G.nodes.empty())
    {
        cout << "Graafil pole veel tippe." << endl;
        return;
    }

    auto it = G.nodes.begin();
    cout << "Graafi tipud: " << (*it)->m_name;
    it++;
    while (it!=G.nodes.end())
    {
        cout << ", " << (*it)->m_name;
        it++;
    }
    cout << endl << endl;

    cout << "Sisesta esimese tipu nimi: ";
    string tipp1;
    getline(cin, tipp1);

    if (G.node_map.find(tipp1) == G.node_map.end())
    {
        cout << "Tippu '" << tipp1 << "' ei olnud olemas." << endl;
        return;
    }

    cout << "Sisesta teise tipu nimi: ";
    string tipp2;
    getline(cin, tipp2);

    if (G.node_map.find(tipp2) == G.node_map.end())
    {
        cout << "Tippu '" << tipp2 << "' ei olnud olemas." << endl;
        return;
    }

    cout << endl;

    shared_ptr<Node> algus = G.node_map[tipp1];
    shared_ptr<Node> lopp = G.node_map[tipp2];
    
    double kaugus = G.findMinDistanceDjikstra(algus, lopp);

    if (kaugus != INFINITY)
    {
        cout << "Minimaalse teekonna kaal: " << kaugus << endl;
        
        stack<shared_ptr<Node>> teekonnaStack;
        shared_ptr<Node> praegune = lopp->m_previousNode;
    
        while (praegune != algus) {
            teekonnaStack.push(praegune);
            praegune = praegune->m_previousNode;
        }

        cout << "Teekond: " << algus->m_name << " -> ";

        while (!teekonnaStack.empty())
        {
            cout << teekonnaStack.top()->m_name << " -> ";
            teekonnaStack.pop();
        }

        cout << lopp->m_name << endl;
    }
    else {
        cout << "Ei leidu teekonda tipust " << tipp1 << " tippu " << tipp2 << "." << endl;
    }

    for (shared_ptr<Node> node : G.nodes) {
        node->m_minDistance = INFINITY;
        node->m_previousNode = NULL;
    }
}

void handleFileCreationInfo() {
    cout << "Graafi csv-fail tuleb paigutada projekti kausta." << endl;
    cout << "Faili esimesel real peavad olema komaga eraldatult graafi tippude nimed." << endl;
    cout << "Faili jargmistel ridadel tuleb esitada kaared formaadis:" << endl;
    cout << "{algTipuNimi},{loppTipuNimi},{kaareKaal}" << endl;
    cout << "Naidiseks vaata faili 'graaf.csv'." << endl;
}

void diplayHeader() {
    cout << "###################################################################################################" << endl;
    cout << "#  ____            _           _     ____  _  _ _        _                                        #" << endl;
    cout << "# |  _ \\ _ __ ___ (_) ___  ___| |_  |  _ \\(_)(_) | _____| |_ _ __ __ _                            #" << endl;
    cout << "# | |_) | '__/ _ \\| |/ _ \\/ __| __| | | | | || | |/ / __| __| '__/ _` |                           #" << endl;
    cout << "# |  __/| | | (_) | |  __/ (__| |_  | |_| | || |   <\\__ \\ |_| | | (_| |                           #" << endl;
    cout << "# |_|   |_|  \\___// |\\___|\\___|\\__| |____/|_|/ |_|\\_\\___/\\__|_|  \\__,_|                           #" << endl;
    cout << "#               |__/                       |__/                                                   #" << endl;
    cout << "###################################################################################################" << endl;
    cout << "# Dijkstra algoritm tootab sammhaaval, kus igal sammul valitakse graafist tipp, mida siiani pole  #" << endl;
    cout << "# vaadatud ning milleni teekond algtipust on vahim. Sellel hetkel fikseeritakse vaadeldava tipu   #" << endl;
    cout << "# kaugus algtipust kui minimaalse teekonna pikkus vaadeldava tipuni, kuna pole enam voimalik      #" << endl;
    cout << "# leida luhemat teekonda tollesse tippu.                                                          #" << endl;
    cout << "# Seejarel vaatab algoritm labi koik vaadeldavast tipust valjuvad kaared. Kui teekond kaare       #" << endl;
    cout << "# lopptippu labi vaadeldava tipu on luhem kui selleks hetkeks teadaolev luhim teekond, siis saab  #" << endl;
    cout << "# sellest lopptipu uus kaugus.                                                                    #" << endl;
    cout << "# Algoritm lopetab too, kui on fikseeritud otsitava lopptipu minimaalne kaugus voi koik graafi    #" << endl;
    cout << "# tipud on labi vaadatud.                                                                         #" << endl;
    cout << "###################################################################################################" << endl;
    cout << "# Antud programm leiab minimaalse kauguse graafi kahe tipu vahel Dijkstra algoritmiga.            #" << endl;
    cout << "# Graaf tuleb ette anda .csv failina.                                                             #" << endl;
    cout << "# Faili voib luua ise voi kasutada naidisena moeldud faili 'graaf.csv'.                           #" << endl;
    cout << "###################################################################################################" << endl;
}

void handleChoosingAction(string& tegevus) {
    cout << endl;
    cout << "Tegevused:" << endl;
    cout << "(0) Sulge programm." << endl;
    cout << "(1) Loe graaf failist sisse." << endl;
    cout << "(2) Kuva graafi info." << endl;
    cout << "(3) Leia tippudevaheline kaugus." << endl;
    cout << "(4) Kuva graafi faili loomise juhend." << endl;
    cout << "Vali tegevuse number: ";

    getline(cin, tegevus);
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
}

int main(int argc, char* argv[]) {
    string tegevus;
    Graph G{};
    
    diplayHeader();
    
    //handleGraphReading(G, true); // Graafi sisselugemine testimise kiirendamiseks.
    
    while (tegevus != "0") {
        handleChoosingAction(tegevus);

        if (tegevus == "0") {
            break;
        }
        else if (tegevus == "1") {
            handleGraphReading(G);
        }
        else if (tegevus == "2") {
            handleDisplayingGraphInfo(G);
        }
        else if (tegevus == "3") {
            handleDistanceMeasurement(G);
        }
        else if (tegevus == "4") {
            handleFileCreationInfo();
        }
        else {
            cout << "Tegevus '" << tegevus << "' ei ole defineeritud." << endl;
        }

        cout << endl;
        cout << "###################################################################################################" << endl;

    }

}


