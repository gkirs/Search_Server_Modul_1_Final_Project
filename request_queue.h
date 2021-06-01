#pragma once
#include "search_server.h"
#include <deque>

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);

    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate);
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);
    std::vector<Document> AddFindRequest(const std::string& raw_query);

    int GetNoResultRequests() const;
private:
    struct QueryResult {
        std::vector<Document> found_docs;
    };
    std::deque<QueryResult> requests_;
    const static int sec_in_day_ = 1440;
    int no_result_requests_ = 0;
    const SearchServer& server;
};

template <typename DocumentPredicate>
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
    QueryResult request;

    request.found_docs = server.FindTopDocuments(raw_query, document_predicate);
    if (request.found_docs.empty()) no_result_requests_++;
    requests_.push_back(request);
    if (requests_.size() > sec_in_day_) {
        if (requests_.front().found_docs.empty()) no_result_requests_--;
        requests_.pop_front();
    }

    return request.found_docs;
}
