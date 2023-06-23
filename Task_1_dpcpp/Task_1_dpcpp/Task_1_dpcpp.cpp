#include <string>
#include <iostream>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};

class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::string reversed_data = data;
        std::reverse(reversed_data.begin(), reversed_data.end());
        text_->render(reversed_data);
    }
};

class Link : public DecoratedText {
public:
    Link(Text* text, const std::string& url) : DecoratedText(text), url_(url) {}
    void render(const std::string& link_data) const {
        std::cout << "<a href=" << url_ << '>';
        text_->render(link_data);
        std::cout << "</a>";
    }
private:
    const std::string url_;
};

int main() {

    setlocale(LC_ALL, "rus");

    auto text_block = new ItalicText(new BoldText(new Text()));
    text_block->render("Hello world");

    std::cout << std::endl;

    auto paragraph_block = new Paragraph(new Text());
    paragraph_block->render("Hello world");

    std::cout << std::endl;

    auto reversed_block = new Reversed(new Text());
    reversed_block->render("Hello world");

    std::cout << std::endl;

    auto link_block = new Link(new Text(), "netology.ru");
    link_block->render("Hello world");

    std::cout << std::endl;

    return 0;
}