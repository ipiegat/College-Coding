from parser import build_open_box_sections, fetch_and_parse_categories, extract_hot_items, format_cards_to_html, diff_cards
from emailer import send_email
from storage import rotate_data_files, save_current_data, load_previous_data
from config import CATEGORIES, HOT_KEYWORDS

def main():
    rotate_data_files()

    all_new_cards, section_blocks = fetch_and_parse_categories()
    save_current_data(all_new_cards)
    all_old_cards = load_previous_data()

    new_items = diff_cards(all_new_cards, all_old_cards)
    hot_items = extract_hot_items(new_items)
    hot_html = format_cards_to_html("🔥 Hot Deals (New or Updated)", hot_items)

    open_box_sections = build_open_box_sections()

    if open_box_sections or hot_items or any(section_blocks):
        full_html = "\n<hr>\n".join(open_box_sections + [hot_html] + section_blocks)
        send_email("🛒 Microcenter Updates — Open Box + Hot + Diffs", full_html)
    else:
        print("📭 No changes to report.")

if __name__ == "__main__":
    main()
