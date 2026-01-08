EMAIL_HOST = "smtp.gmail.com"
EMAIL_PORT = 587
EMAIL_USER = "isaacpiegat@gmail.com"
EMAIL_PASS = "txcw yvls yinj jpvr"
EMAIL_TO   = "isaacpiegat@gmail.com"

CATEGORIES = [
    ("Processors/CPUs",     "https://www.microcenter.com/search/search_results.aspx?N=4294966995&NTK=all&sortby=match&rpp=96"),
    ("Graphics Cards",      "https://www.microcenter.com/search/search_results.aspx?N=4294966937&NTK=all&sortby=match&rpp=96"),
    ("Motherboards",        "https://www.microcenter.com/search/search_results.aspx?N=4294966996&NTK=all&sortby=match&rpp=96"),
    ("Drives & Storage",    "https://www.microcenter.com/search/search_results.aspx?N=4294966964&NTK=all&sortby=match&rpp=96"),
    ("Computer Memory",     "https://www.microcenter.com/search/search_results.aspx?N=4294966965&NTK=all&sortby=match&rpp=96"),
    ("Computer Cases",      "https://www.microcenter.com/search/search_results.aspx?N=4294966966&NTK=all&sortby=match&rpp=96"),
    ("Power Supplies",      "https://www.microcenter.com/search/search_results.aspx?N=4294966967&NTK=all&sortby=match&rpp=96"),
    ("Air & Water Cooling", "https://www.microcenter.com/search/search_results.aspx?N=4294966969&NTK=all&sortby=match&rpp=96"),
]

OPEN_BOX = [
    ("🟦 Open Box GPUs", "https://www.microcenter.com/search/search_results.aspx?Ntk=all&sortby=match&prt=clearance&N=4294966937&myStore=true"),
    ("🟦 Open Box CPUs", "https://www.microcenter.com/search/search_results.aspx?Ntk=all&sortby=match&prt=clearance&N=4294966995&myStore=true"),
]

HOT_KEYWORDS = ["5060 Ti", "7800X3D", "Refurbished"]
HEADERS = {"User-Agent": "Mozilla/5.0"}

BASE_DIR = r"Personal/Mini-Projects/Bot"
DATA_TODAY = BASE_DIR + "\\data_today.json"
DATA_YESTERDAY = BASE_DIR + "\\data_yesterday.json"
