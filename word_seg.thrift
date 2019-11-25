namespace cpp WordSeg

struct WordSegRequest 
{
    1: string       query_id,
    2: string       query
}

struct WordSegResponse
{
    1: list<string>         tokens,
    2: list<i32>            begin_idx,
    3: list<i32>            end_idx
}

service WordSegService {
    WordSegResponse word_segment(1:WordSegRequest req) throws (1:WordSegException e)
}
