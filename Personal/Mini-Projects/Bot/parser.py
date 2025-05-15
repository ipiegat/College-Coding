import requests
import time
from bs4 import BeautifulSoup
from selenium import webdriver
from config import HEADERS, HOT_KEYWORDS, OPEN_BOX, CATEGORIES
from storage import load_previous_data
import html

def fetch_html(url):
    res = requests.get(url, headers=HEADERS)
    res.raise_for_status()
    return res.text

def parse_cards(html):
    soup = BeautifulSoup(html, "html.parser")
    cards = soup.select('a.image2.productClickItemV2[data-price]')
    results = []
    for c in cards:
        name = c["data-name"]
        price = float(c["data-price"])
        href = c["href"]
        link = f"https://www.microcenter.com{href}"
        results.append({
            "name": name,
            "price": price,
            "link": link
        })
    return results

def extract_hot_items(all_cards):
    return sorted(
        [c for c in all_cards if any(k.lower() in c["name"].lower() for k in HOT_KEYWORDS)],
        key=lambda x: x["price"]
    )

def format_cards_to_html(title, cards):
    if not cards:
        return f"<h3 style='margin-top:30px; font-size:18px; border-bottom:2px solid #eee; padding-bottom:5px;'>{title}</h3><p>No updates.</p>"

    def format_delta(delta):
        if delta is None:
            return "—"
        if delta > 0:
            return f'<span style="color:red;">+${delta:.2f}</span>'
        if delta < 0:
            return f'<span style="color:green;">−${abs(delta):.2f}</span>'
        return "—"

    rows = []
    for c in cards:
        name = html.escape(c.get("name", "Unknown"))
        price = float(c.get("price", 0))
        link = html.escape(c.get("link", "#"))
        delta_html = format_delta(c.get("delta"))

        row = f"""
        <tr>
            <td style="padding:6px 8px;">
                <a href="{link}" style="color:#0078D4; text-decoration:none;">{name}</a>
            </td>
            <td style="padding:6px 8px; text-align:right;">${price:.2f}</td>
            <td style="padding:6px 8px; text-align:right;">{delta_html}</td>
        </tr>
        """
        rows.append(row)

    table = f"""
    <h3 style="margin-top:30px; font-size:18px; border-bottom:2px solid #eee; padding-bottom:5px;">{title}</h3>
    <table style="width:100%; border-collapse:collapse; font-family:Segoe UI, sans-serif;">
        <thead>
            <tr style="background-color:#f2f2f2;">
                <th align="left" style="padding:8px; border-bottom:1px solid #ccc;">Product</th>
                <th align="right" style="padding:8px; border-bottom:1px solid #ccc;">Price</th>
                <th align="right" style="padding:8px; border-bottom:1px solid #ccc;">Δ Change</th>
            </tr>
        </thead>
        <tbody>
            {''.join(rows)}
        </tbody>
    </table>
    """
    return table

def diff_cards(new_cards, old_cards):
    old_lookup = {(c["name"], c["link"]): c["price"] for c in old_cards}
    changed = []
    for c in new_cards:
        key = (c["name"], c["link"])
        old_price = old_lookup.get(key)
        if old_price is None or old_price != c["price"]:
            delta = None if old_price is None else round(c["price"] - old_price, 2)
            c["delta"] = delta
            changed.append(c)
    return changed

def build_open_box_sections():
    open_box_sections = []

    options = webdriver.ChromeOptions()
    options.add_argument("--headless")
    options.add_argument("--disable-gpu")
    options.add_argument("--window-size=1920,1080")
    driver = webdriver.Chrome(options=options)

    driver.get("https://www.microcenter.com/site/store/selectstore.aspx?storeid=029")
    time.sleep(0.3)

    for label, url in OPEN_BOX:
        try:
            driver.get(url)
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

            results.sort(key=lambda x: x[0])

            open_box_sections.append(format_open_box_to_table(label, results))


        except Exception as e:
            open_box_sections.append(f"<h3>{label}</h3><p>Error: {e}</p>")

    driver.quit()
    return open_box_sections

import html

def format_open_box_to_table(title, items):
    if not items:
        return f"<h3 style='margin-top:30px; font-size:18px; border-bottom:2px solid #eee; padding-bottom:5px;'>{title}</h3><p>No items found.</p>"

    rows = []
    for reduced, original, name, link in items:
        name = html.escape(name)
        link = html.escape(link)
        row = f"""
        <tr>
            <td style="padding:6px 8px;">
                <a href="{link}" style="color:#0078D4; text-decoration:none;">{name}</a>
            </td>
            <td style="padding:6px 8px; text-align:right;">${original:.2f}</td>
            <td style="padding:6px 8px; text-align:right;">
                <strong>${reduced:.2f}</strong>
            </td>
        </tr>
        """
        rows.append(row)

    table = f"""
    <h3 style="margin-top:30px; font-size:18px; border-bottom:2px solid #eee; padding-bottom:5px;">{title}</h3>
    <table style="width:100%; border-collapse:collapse; font-family:Segoe UI, sans-serif;">
        <thead>
            <tr style="background-color:#f2f2f2;">
                <th align="left" style="padding:8px; border-bottom:1px solid #ccc;">Product</th>
                <th align="right" style="padding:8px; border-bottom:1px solid #ccc;">Original</th>
                <th align="right" style="padding:8px; border-bottom:1px solid #ccc;">Open Box</th>
            </tr>
        </thead>
        <tbody>
            {''.join(rows)}
        </tbody>
    </table>
    """
    return table

def fetch_and_parse_categories():
    all_new_cards = []
    section_blocks = []

    all_old_cards = load_previous_data()

    for name, url in CATEGORIES:
        html = fetch_html(url)
        cards = parse_cards(html)
        all_new_cards.extend(cards)

        # 🔥 Only include products with changed prices
        filtered_cards = diff_cards(cards, all_old_cards)
        section_blocks.append((name, filtered_cards))

    return all_new_cards, [
        format_cards_to_html(name, cards) for name, cards in section_blocks
    ]