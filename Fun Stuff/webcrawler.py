"""
get a random wiki page
get text from it
run sentiment analysis

print page name and analysis result
"""

import urllib.request
from html.parser import HTMLParser

# Part 1: Get a random wiki page

random_gen_url = "https://en.wikipedia.org/wiki/Special:Random"

page = urllib.request.urlopen(random_gen_url)
wiki_HTML = page.read().decode("utf-8")
print("Got wiki HTML")

# Part 2: Parse the HTML, get the text body]

target_div_id = "mw-content-text"


class MyHTMLParser(HTMLParser):
    def __init__(self):
        self.in_target_div = False
        self.depth = 0

        self.in_style_section = False
        self.style_depth = 0

        self.body_text = ""
        super().__init__()

    def handle_starttag(self, tag, attrs):
        if tag == "div":
            for k, v in attrs:
                if k == "id" and v == target_div_id:
                    print("Found target div ID")
                    self.in_target_div = True

        if self.in_target_div:
            self.depth += 1

        if tag == "style":
            self.in_style_section = True

        if self.in_style_section:
            self.style_depth += 1

    def handle_endtag(self, tag):
        if self.in_target_div:
            self.depth -= 1

            if self.depth == 0:
                print("Leaving target div")
                self.in_target_div = False

        if self.in_style_section:
            self.style_depth -= 1

            if self.style_depth == 0:
                self.in_style_section = False

    def handle_data(self, data):
        if not self.in_target_div:
            return

        if self.in_style_section:
            return

        stripped = data.strip()
        if len(stripped) > 0:
            self.body_text += " " + stripped


parser = MyHTMLParser()
parser.feed(wiki_HTML)

print(
    "=========================================ALL TEXT=========================================\n\n"
)
print(parser.body_text)
