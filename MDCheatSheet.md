MARKDOWN QUICK REFERENCE CHEAT SHEET
(GitHub Flavored Markdown – 2026 edition)

1. HEADERS
# H1 – Main Title
## H2 – Section
### H3 – Subsection
#### H4
##### H5
###### H6 – Smallest

2. TEXT EMPHASIS & STYLING
*italic*     or     _italic_
**bold**     or     __bold__
***bold + italic***
~~strikethrough~~

`inline code`                 →  inline code

> Blockquote                  →  indented quote block

***                           →  horizontal rule (or --- or ___)

3. LISTS

Unordered
- Item          (or * or +)
- Item
  - Sub-item
  - Sub-item

Ordered
1. First
2. Second
   1. Sub-item
   2. Sub-item
3. Third

Task lists (great for GitHub issues & PRs)
- [ ] Todo
- [x] Done
- [ ] Another task

4. LINKS & IMAGES
[Link text](https://example.com)

[Link with title](https://example.com "Hover tooltip")

![Alt text](https://example.com/image.jpg)

![Image with title](https://example.com/pic.png "Optional title")

5. CODE

Inline
Use `console.log("hi")` for quick code.

Code block (language for syntax highlighting)
```python
def greet(name):
    return f"Hello, {name}!"