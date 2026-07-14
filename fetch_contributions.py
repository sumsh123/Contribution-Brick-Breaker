import requests
import re


username = "sumsh123"

url = f"https://github.com/users/{username}/contributions"


headers = {
    "User-Agent": "Mozilla/5.0"
}


html = requests.get(
    url,
    headers=headers
).text


levels = re.findall(
    r'data-level="([0-4])"',
    html
)


print("Found:", len(levels))


if len(levels) == 0:
    print("Failed loading contributions")
    exit()


with open(
    "contributions.txt",
    "w"
) as f:

    for level in levels:
        f.write(level+"\n")


print("Saved contribution data!")