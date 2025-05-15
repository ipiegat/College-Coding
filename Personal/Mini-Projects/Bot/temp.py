from selenium import webdriver
from bs4 import BeautifulSoup
import time

options = webdriver.ChromeOptions()
options.add_argument("--headless")
options.add_argument("--disable-gpu")
options.add_argument("--window-size=1920,1080")
driver = webdriver.Chrome(options=options)

# Set store to Yonkers
driver.get("https://www.microcenter.com/site/store/selectstore.aspx?storeid=029")
time.sleep(0.3)

# Load Open Box GPU page
driver.get("https://www.microcenter.com/search/search_results.aspx?Ntk=all&sortby=match&prt=clearance&N=4294966937")
time.sleep(1)

soup = BeautifulSoup(driver.page_source, "html.parser")
anchors = soup.select('a.productClickItemV2[data-name][data-price][href]')

seen_links = set()
results = []

for a in anchors:
    link = f"https://www.microcenter.com{a['href']}"
    if link in seen_links:
        continue
    seen_links.add(link)

    name = a['data-name'].strip()
    original_price = float(a['data-price'])

    driver.get(link)
    time.sleep(0.5)
    soup_box = BeautifulSoup(driver.page_source, "html.parser")
    divs = soup_box.select('div.pricing[data-price]')
    reduced_price = float(divs[0]['data-price']) if divs else original_price

    results.append((reduced_price, original_price, name, link))

driver.quit()

# Sort by reduced price
results.sort(key=lambda x: x[0])

# Print final sorted list
for reduced_price, original_price, name, link in results:
    print(f"${original_price:.2f} → ${reduced_price:.2f} - {name} — {link}")
