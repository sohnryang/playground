from django.http import HttpRequest, HttpResponse
from django.shortcuts import get_object_or_404, render

from .models import Question


def index(request: HttpRequest) -> HttpResponse:
    latest_question_list = Question.objects.order_by("-pub_date")[:5]
    context = {"latest_question_list": latest_question_list}
    return render(request, "polls/index.html", context)


def detail(request: HttpRequest, question_id: int) -> HttpResponse:
    question = get_object_or_404(Question, pk=question_id)
    return render(request, "polls/detail.html", {"question": question})


def results(request: HttpRequest, question_id: int) -> HttpResponse:
    return HttpResponse(f"Results of question with id {question_id}".encode())


def vote(request: HttpRequest, question_id: int) -> HttpResponse:
    return HttpResponse(f"Voting on question with id {question_id}".encode())
