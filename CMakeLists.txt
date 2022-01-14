cmake_minimum_required(VERSION 3.2)

project(Chess)

add_library(Cell
    header_files/Cell.h
    cpp_files/Cell.cpp
)

add_library(Piece
    header_files/Piece.h
    cpp_files/Piece.cpp
)

add_library(Bishop
    header_files/Bishop.h
    cpp_files/Bishop.cpp
)

add_library(King
    header_files/King.h
    cpp_files/King.cpp
)

add_library(Knight
    header_files/Knight.h
    cpp_files/Knight.cpp
)

add_library(Pawn
    header_files/Pawn.h
    cpp_files/Pawn.cpp
)

add_library(Queen
    header_files/Queen.h
    cpp_files/Queen.cpp
)

add_library(Rook
    header_files/Rook.h
    cpp_files/Rook.cpp
)

add_library(Chessboard
    header_files/Chessboard.h
    cpp_files/Chessboard.cpp
)

add_library(Player
    header_files/Player.h
    cpp_files/Player.cpp
)

add_library(Human
    header_files/Human.h
    cpp_files/Human.cpp
)

add_library(Computer
    header_files/Computer.h
    cpp_files/Computer.cpp
)

add_executable(main
    main.cpp
)

target_link_libraries(main
    Chessboard
    Cell
    King
    Knight
    Pawn
    Queen
    Rook
    Bishop
    Piece
    Human
    Computer
    Player
)