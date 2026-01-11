FROM gcc:13
WORKDIR /src
COPY . .
RUN g++ -O2 -std=c++17 -o wordle *.cpp
CMD ["/src/wordle"]
